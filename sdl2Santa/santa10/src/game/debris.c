/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "debris.h"
#include "entities.h"

static void tick(Entity *self);
static void draw(Entity *self);

extern App   app;
extern Stage stage;

void initDebris(int x, int y, AtlasImage *texture)
{
	Entity *e;

	e = spawnEntity();
	e->x = x;
	e->y = y;
	e->dx = 0.1 * (rand() % 50 - rand() % 50);
	e->dy = -(8 + rand() % 8);
	e->texture = texture;

	e->tick = tick;
	e->draw = draw;
}

static void tick(Entity *self)
{
	self->dy += 0.5 * app.deltaTime;

	self->x += self->dx * app.deltaTime;
	self->y += self->dy * app.deltaTime;

	self->dead = self->y > SCREEN_HEIGHT;
}

static void draw(Entity *self)
{
	blitAtlasImage(self->texture, self->x, self->y, 0, SDL_FLIP_NONE);
}
