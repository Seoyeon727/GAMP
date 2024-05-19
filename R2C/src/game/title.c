/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "../system/sound.h"
#include "../system/text.h"
#include "../system/textures.h"
#include "highscores.h"
#include "stage.h"
#include "title.h"

#define SHOW_TIME (FPS * 5)

static void logic(void);
static void draw(void);

static SDL_Texture *titleTexture = NULL;
static double       showTimer;
static int          showScores;

extern App   app;
extern Game  game;
extern Stage stage;

void initTitle(void)
{
	if (titleTexture == NULL)
	{
		titleTexture = loadTexture("gfx/sdl2Santa.png");
	}

	initStage();

	showTimer = SHOW_TIME;

	showScores = game.latestHighscore != NULL;

	resumeMusic();

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	doStage();

	showTimer -= app.deltaTime;

	if (showTimer <= 0)
	{
		showTimer += SHOW_TIME;

		showScores = !showScores;
	}

	if (app.keyboard[SDL_SCANCODE_SPACE])
	{
		app.keyboard[SDL_SCANCODE_SPACE] = 0;

		initStage();

		startStage();
	}
}

static void draw(void)
{
	drawStage();

	if (!showScores)
	{
		blit(titleTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 1, SDL_FLIP_NONE);
	}
	else
	{
		drawHighScores();
	}

	app.fontScale = 1.25;

	drawShadowText("Press SPACE to Play!", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 150, 128, 255, 128, TEXT_ALIGN_CENTER);

	app.fontScale = 0.65;

	drawShadowText("Copyright 2023, Parallel Realities. All Rights Reserved.", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30, 160, 160, 160, TEXT_ALIGN_CENTER);

	app.fontScale = 1.0;
}
