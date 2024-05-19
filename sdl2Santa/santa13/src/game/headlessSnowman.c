/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "entities.h"
#include "player.h"
#include "snowman.h"
#include "snowmanHead.h"

static void tick(Entity *self);
static void draw(Entity *self);
static void touch(Entity *self, Entity *other);

static AtlasImage *texture = NULL;

extern App   app;
extern Stage stage;

void initHeadlessSnowman(void)
{
	Entity *e;
	int     x, y;

	if (texture == NULL)
	{
		texture = getAtlasImage("gfx/headlessSnowman.png", 1);
	}

	x = SCREEN_WIDTH + 200 + rand() % 100;
	y = GROUND_Y - texture->rect.h;

	if (canAddEntity(x, y, texture->rect.w, texture->rect.h))
	{
		initSnowmanHead(x + 5, y - 16);

		e = spawnEntity();
		e->type = ET_HEADLESS_SNOWMAN;
		e->x = x;
		e->y = y;
		e->texture = texture;

		e->tick = tick;
		e->draw = draw;
		e->touch = touch;
	}
}

static void tick(Entity *self)
{
	self->x -= stage.speed * app.deltaTime;

	self->dead = self->x < -self->texture->rect.w;
}

static void draw(Entity *self)
{
	blitAtlasImage(self->texture, self->x, self->y, 0, SDL_FLIP_NONE);
}

static void touch(Entity *self, Entity *other)
{
	if (other == stage.player)
	{
		killPlayer(-1, -1);
	}
}
