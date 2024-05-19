/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/textures.h"
#include "entities.h"
#include "highscores.h"
#include "house.h"
#include "hud.h"
#include "player.h"
#include "sack.h"
#include "snowman.h"
#include "stage.h"
#include "title.h"

#define INITIAL_GROUND_SPEED 2
#define MAX_GROUND_SPEED     6.5
#define GROUND_WIDTH         ((SCREEN_WIDTH / GROUND_TILE_SIZE) + 1)
#define NUM_GROUND_TEXTURES  5

static void doGround(void);
static void addHouse(void);
static void addObject(void);
static void drawGround(void);
static void initGround(void);
static void loadTextures(void);
static void resetStage(void);

static double       objectSpawnTimer;
static double       groundX;
static double       gameOverTimer;
static int          ground[GROUND_WIDTH];
static AtlasImage  *groundTextures[NUM_GROUND_TEXTURES] = {NULL};
static double       houseSpawnTimer;
static int          reset = 0;
static SDL_Texture *xmasCancelledTexture;

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

	initEntities();

	initGround();

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

		objectSpawnTimer = FPS * 5 + ((int)FPS * rand() % 5);
	}
}

void drawStage(void)
{
	drawGround();

	drawEntities();

	if (stage.state != SS_DEMO)
	{
		drawHUD();
	}

	if (stage.state == SS_GAME_OVER && stage.speed < 1)
	{
		blit(xmasCancelledTexture, SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 100, 1, SDL_FLIP_NONE);
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

	xmasCancelledTexture = loadTexture("gfx/xmasCancelled.png");
}
