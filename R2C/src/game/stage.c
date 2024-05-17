/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/textures.h"
#include "entities.h"
#include "headlessSnowman.h"
#include "highscores.h"
#include "house.h"
#include "hud.h"
#include "particles.h"
#include "player.h"
#include "quadtree.h"
#include "sack.h"
#include "snow.h"
#include "snowman.h"
#include "stage.h"
#include "title.h"

#define INITIAL_GROUND_SPEED 2
#define MAX_GROUND_SPEED     6.5
#define GROUND_WIDTH         ((SCREEN_WIDTH / GROUND_TILE_SIZE) + 1)
#define NUM_GROUND_TEXTURES  5
#define NUM_TREE_TEXTURES    4
#define NUM_HILLS_LAYERS     2

static void doGround(void);
static void addHouse(void);
static void addObject(void);
static void drawGround(void);
static void drawHills(void);
static void doHills(void);
static void initGround(void);
static void initHills(void);
static void loadTextures(void);
static void resetStage(void);
static int  treeComparator(const void *a, const void *b);

static double       objectSpawnTimer;
static double       groundX;
static double       gameOverTimer;
static int          ground[GROUND_WIDTH];
static AtlasImage  *groundTextures[NUM_GROUND_TEXTURES] = {NULL};
static double       houseSpawnTimer;
static int          reset = 0;
static SDL_Texture *xmasCancelledTexture;
static AtlasImage  *treeTextures[NUM_TREE_TEXTURES];
static Hills        hillLayers[NUM_HILLS_LAYERS];

extern App   app;
extern Stage stage;

void initStage(void)
{
	if (reset)
	{
		resetStage();
	}

	reset = 1;

	memset(&stage, 0, sizeof(Stage));

	if (groundTextures[0] == NULL)
	{
		loadTextures();
	}

	initQuadtree(&stage.quadtree);

	initEntities();

	initGround();

	initHills();

	initSnow();

	initParticles();

	stage.state = SS_DEMO;

	houseSpawnTimer = FPS;

	objectSpawnTimer = FPS * 5 + ((int)FPS * rand() % 5);

	gameOverTimer = FPS * 5;

	app.delegate.logic = doStage;
	app.delegate.draw = drawStage;
}

static void initGround(void)
{
	int i;

	for (i = 0; i < GROUND_WIDTH; i++)
	{
		ground[i] = rand() % NUM_GROUND_TEXTURES;
	}
}

static void initHills(void)
{
	int    i;
	Tree  *t;
	Hills *h;

	memset(&hillLayers, 0, sizeof(Hills) * NUM_HILLS_LAYERS);

	h = &hillLayers[0];
	h->y = 350;
	h->amplitude = 8;
	h->period = 0.1;
	h->speed = 0.005;
	h->color.r = h->color.g = 120;
	h->color.b = 130;
	h->numTrees = MAX_HILL_TREES;

	h = &hillLayers[1];
	h->y = 150;
	h->amplitude = 24;
	h->period = 0.05;
	h->speed = 0.01;
	h->color.r = h->color.g = 190;
	h->color.b = 200;

	h = &hillLayers[0];

	for (i = 0; i < h->numTrees; i++)
	{
		h = &hillLayers[0];
		t = &h->trees[i];

		t->x = rand() % SCREEN_WIDTH;
		t->y = (GROUND_Y - h->y - treeTextures[0]->rect.h + h->amplitude) + rand() % 150;
		t->texture = treeTextures[rand() % NUM_TREE_TEXTURES];
		t->speed = (t->y / h->y) * 1.25;
	}

	qsort(h->trees, h->numTrees, sizeof(Tree), treeComparator);
}

void startStage(void)
{
	stage.speed = INITIAL_GROUND_SPEED;
	stage.xmasSpirit = MAX_XMAS_SPIRIT;
	stage.numGifts = 12;
	stage.numCoal = 12;

	initPlayer();

	initHUD();

	stage.state = SS_PLAYING;
}

void doStage(void)
{
	switch (stage.state)
	{
		case SS_PLAYING:
			stage.speed = MIN(stage.speed + (0.00025 * app.deltaTime), MAX_GROUND_SPEED);
			break;

		case SS_GAME_OVER:
			stage.speed *= 1 - (0.01 * app.deltaTime);

			gameOverTimer -= app.deltaTime;

			if (gameOverTimer <= 0)
			{
				addHighscore();

				initTitle();
			}
			break;

		default:
			stage.speed = INITIAL_GROUND_SPEED;
			break;
	}

	stage.pauseTimer = MAX(stage.pauseTimer - app.deltaTime, 0);

	if (stage.pauseTimer == 0)
	{
		doGround();

		doHills();

		addHouse();

		if (stage.state == SS_PLAYING)
		{
			addObject();
		}

		if (stage.state != SS_DEMO)
		{
			doHUD();
		}

		doEntities();

		doSnow();

		doParticles();

		if (stage.xmasSpirit == 0 && stage.player != NULL)
		{
			killPlayer(-1, -1);
		}
	}
}

static void doGround(void)
{
	groundX -= stage.speed * app.deltaTime;
}

static void doHills(void)
{
	int    i, j;
	double x, speed;
	Hills *h;
	Tree  *t;

	speed = (stage.speed / 4);

	for (i = 0; i < NUM_HILLS_LAYERS; i++)
	{
		h = &hillLayers[i];

		x = h->startX;

		for (j = 0; j < HILLS_HEIGHT_LENGTH; j++)
		{
			h->heights[j] = h->y + sin(x) * h->amplitude;

			x -= h->period;
		}

		h->startX -= h->speed * speed * app.deltaTime;

		for (j = 0; j < h->numTrees; j++)
		{
			t = &h->trees[j];

			t->x -= t->speed * speed * app.deltaTime;

			if (t->x < -t->texture->rect.w)
			{
				t->x += SCREEN_WIDTH + t->texture->rect.w;
			}
		}
	}
}

static void addHouse(void)
{
	houseSpawnTimer -= stage.speed * app.deltaTime;

	if (houseSpawnTimer <= 0)
	{
		initHouse();

		houseSpawnTimer = rand() % SCREEN_WIDTH / 2;
	}
}

static void addObject(void)
{
	int n;

	objectSpawnTimer -= stage.speed * app.deltaTime;

	if (objectSpawnTimer <= 0)
	{
		n = rand() % 100;

		if (n < 15)
		{
			initSack(ET_GIFT_SACK);
		}
		else if (n < 30)
		{
			initSack(ET_COAL_SACK);
		}
		else if (n < 50)
		{
			initSnowman();
		}
		else if (n < 65)
		{
			initHeadlessSnowman();
		}

		objectSpawnTimer = FPS * 5 + ((int)FPS * rand() % 5);
	}
}

void drawStage(void)
{
	drawHills();

	drawGround();

	drawEntities();

	drawParticles();

	drawSnow();

	if (stage.state != SS_DEMO)
	{
		drawHUD();
	}

	if (stage.state == SS_GAME_OVER && stage.speed < 1)
	{
		blit(xmasCancelledTexture, SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 100, 1, SDL_FLIP_NONE);
	}
}

static void drawHills(void)
{
	int    i, j;
	Hills *h;
	Tree  *t;

	for (i = 0; i < 24; i++)
	{
		drawRect(0, i * 24, SCREEN_WIDTH, 24, i, i + 8, i + 40, 255);
	}

	for (i = 0; i < NUM_HILLS_LAYERS; i++)
	{
		h = &hillLayers[i];

		for (j = 0; j < HILLS_HEIGHT_LENGTH; j++)
		{
			drawRect(j * HILL_WIDTH, GROUND_Y - h->heights[j], HILL_WIDTH, h->heights[j], h->color.r, h->color.g, h->color.b, 255);
		}

		for (j = 0; j < h->numTrees; j++)
		{
			t = &h->trees[j];

			blitAtlasImage(t->texture, t->x, t->y, 0, SDL_FLIP_NONE);
		}
	}
}

static void drawGround(void)
{
	int i, x, n, t;

	n = (int)groundX * -1 / GROUND_TILE_SIZE;

	x = (int)groundX % GROUND_TILE_SIZE;

	for (i = 0; i < GROUND_WIDTH; i++)
	{
		t = (n + i) % GROUND_WIDTH;

		blitAtlasImage(groundTextures[ground[t]], x, GROUND_Y, 0, SDL_FLIP_NONE);

		x += GROUND_TILE_SIZE;
	}
}

static void resetStage(void)
{
	clearEntities();

	clearParticles();

	destroyQuadtree(&stage.quadtree);
}

static void loadTextures(void)
{
	int  i;
	char filename[MAX_NAME_LENGTH];

	for (i = 0; i < NUM_GROUND_TEXTURES; i++)
	{
		sprintf(filename, "gfx/ground%02d.png", i + 1);
		groundTextures[i] = getAtlasImage(filename, 1);
	}

	for (i = 0; i < NUM_TREE_TEXTURES; i++)
	{
		sprintf(filename, "gfx/tree%02d.png", i + 1);
		treeTextures[i] = getAtlasImage(filename, 1);
	}

	xmasCancelledTexture = loadTexture("gfx/xmasCancelled.png");
}

static int treeComparator(const void *a, const void *b)
{
	Tree *t1, *t2;

	t1 = ((Tree *)a);
	t2 = ((Tree *)b);

	return t1->y - t2->y;
}
