/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "carrot.h"
#include "entities.h"
#include "particles.h"
#include "player.h"

static void tick(Entity *self);
static void draw(Entity *self);
static void touch(Entity *self, Entity *other);

static AtlasImage *texture = NULL;

extern App   app;
extern Stage stage;

void initCarrot(int x, int y)
{
	Entity *e;

	if (texture == NULL)
	{
		texture = getAtlasImage("gfx/carrot.png", 1);
	}

	e = spawnEntity();
	e->type = ET_CARROT;
	e->x = x;
	e->y = y;
	e->texture = texture;
	e->tick = tick;
	e->draw = draw;
	e->touch = touch;
}

static void tick(Entity *self)
{
	self->x -= (stage.speed + 7) * app.deltaTime;

	if (self->x < -self->texture->rect.w)
	{
		self->dead = 1;
	}
}

static void draw(Entity *self)
{
	blitAtlasImage(self->texture, self->x, self->y, 0, SDL_FLIP_NONE);
}

static void touch(Entity *self, Entity *other)
{
	int i;

	if (other == stage.player)
	{
		killPlayer(self->x, self->y);

		self->dead = 1;

		for (i = 0; i < 25; i++)
		{
			addParticle(self->x, self->y, 255, 128 + rand() % 64, 0);
		}
	}
}
