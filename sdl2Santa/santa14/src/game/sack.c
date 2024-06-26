/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "entities.h"
#include "sack.h"

static void tick(Entity *self);
static void draw(Entity *self);
static void touch(Entity *self, Entity *other);

static AtlasImage *giftSackTexture = NULL;
static AtlasImage *coalSackTexture;

extern App   app;
extern Stage stage;

void initSack(int type)
{
	Entity *e;
	Sack   *s;

	if (giftSackTexture == NULL)
	{
		giftSackTexture = getAtlasImage("gfx/giftSack.png", 1);
		coalSackTexture = getAtlasImage("gfx/coalSack.png", 1);
	}

	s = malloc(sizeof(Sack));
	memset(s, 0, sizeof(Sack));
	s->speed = (5.0 + rand() % 10) * 0.1;
	s->startY = 50 + rand() % (SCREEN_HEIGHT / 2);

	e = spawnEntity();
	e->type = type;
	e->x = SCREEN_WIDTH / 2 + (rand() % SCREEN_WIDTH * 0.35);
	e->y = s->startY;
	e->data = s;

	if (type == ET_GIFT_SACK)
	{
		e->texture = giftSackTexture;
	}
	else
	{
		e->texture = coalSackTexture;
	}

	e->tick = tick;
	e->draw = draw;
	e->touch = touch;
}

static void tick(Entity *self)
{
	Sack *s;

	s = (Sack *)self->data;

	s->bob += 0.1 * app.deltaTime;

	self->y = s->startY + (16 * sin(s->bob));

	self->x -= stage.speed * s->speed * app.deltaTime;

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
	if (other == stage.player)
	{
		if (self->type == ET_GIFT_SACK)
		{
			stage.numGifts += 5 + rand() % 5;
		}
		else
		{
			stage.numCoal += 5 + rand() % 5;
		}

		self->dead = 1;
	}
}
