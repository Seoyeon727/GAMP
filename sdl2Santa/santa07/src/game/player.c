/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "entities.h"
#include "gift.h"
#include "player.h"

static void tick(Entity *self);
static void move(Entity *self);
static void draw(Entity *self);
static void dropGift(void);
static void loadTextures(void);

static AtlasImage *sleighTexture = NULL;

extern App   app;
extern Stage stage;

void initPlayer(void)
{
	Entity *e;

	if (sleighTexture == NULL)
	{
		loadTextures();
	}

	e = spawnEntity();
	e->type = ET_PLAYER;
	e->x = 400;
	e->y = 200;
	e->dy = -8;
	e->texture = sleighTexture;

	e->tick = tick;
	e->draw = draw;

	stage.player = e;
}

static void tick(Entity *self)
{
	move(self);

	dropGift();
}

static void move(Entity *self)
{
	double dx;

	dx = 0;

	self->dy += 0.2 * app.deltaTime;

	if (app.keyboard[SDL_SCANCODE_W])
	{
		self->dy -= app.deltaTime;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		self->dy += app.deltaTime;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		dx = -4;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		dx = 4;
	}

	if (dx != 0)
	{
		self->dx += dx * app.deltaTime;
	}
	else
	{
		self->dx = 0;
	}

	self->dx = MAX(MIN(self->dx, 5), -5);
	self->dy = MAX(MIN(self->dy, 5), -5);

	self->x = MIN(MAX(10, self->x + self->dx * app.deltaTime), SCREEN_WIDTH - self->texture->rect.w - 10);

	self->y += self->dy * app.deltaTime;

	if (self->y < 50)
	{
		self->y = 50;
		self->dy = 0;
	}
	else if (self->y + self->texture->rect.h >= GROUND_Y)
	{
		self->y = GROUND_Y - self->texture->rect.h;
		self->dy = 0;
	}
}

static void dropGift(void)
{
	if (app.keyboard[SDL_SCANCODE_J])
	{
		stage.numGifts--;

		app.keyboard[SDL_SCANCODE_J] = 0;

		initGift(ET_GIFT);
	}

	if (app.keyboard[SDL_SCANCODE_L])
	{
		stage.numCoal--;

		app.keyboard[SDL_SCANCODE_L] = 0;

		initGift(ET_COAL);
	}
}

static void draw(Entity *self)
{
	blitAtlasImage(self->texture, self->x, self->y, 0, SDL_FLIP_NONE);
}

static void loadTextures(void)
{
	sleighTexture = getAtlasImage("gfx/sleigh.png", 1);
}
