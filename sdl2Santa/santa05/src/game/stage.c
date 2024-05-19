/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/textures.h"
#include "entities.h"
#include "house.h"
#include "player.h"
#include "stage.h"

#define INITIAL_GROUND_SPEED 2
#define GROUND_WIDTH         ((SCREEN_WIDTH / GROUND_TILE_SIZE) + 1)
#define NUM_GROUND_TEXTURES  5

static void doGround(void);
static void addHouse(void);
static void drawGround(void);
static void initGround(void);
static void loadTextures(void);

static double      groundX;
static int         ground[GROUND_WIDTH];
static AtlasImage *groundTextures[NUM_GROUND_TEXTURES] = {NULL};
static double      houseSpawnTimer;

extern App   app;
extern Stage stage;

void initStage(void)
{
	memset(&stage, 0, sizeof(Stage));

	if (groundTextures[0] == NULL)
	{
		loadTextures();
	}

	initGround();

	initEntities();

	initPlayer();

	stage.speed = INITIAL_GROUND_SPEED;

	houseSpawnTimer = SCREEN_WIDTH / 8;

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

void doStage(void)
{
	doGround();

	addHouse();

	doEntities();
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

void drawStage(void)
{
	drawGround();

	drawEntities();
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

static void loadTextures(void)
{
	int  i;
	char filename[MAX_NAME_LENGTH];

	for (i = 0; i < NUM_GROUND_TEXTURES; i++)
	{
		sprintf(filename, "gfx/ground%02d.png", i + 1);
		groundTextures[i] = getAtlasImage(filename, 1);
	}
}
