/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "entities.h"
#include "gift.h"

#define NUM_GIFT_TEXTURES 5
#define NUM_COAL_TEXTURES 4

static void tick(Entity *self);
static void draw(Entity *self);
static void loadTextures(void);

static AtlasImage *giftTextures[NUM_GIFT_TEXTURES] = {NULL};
static AtlasImage *coalTextures[NUM_COAL_TEXTURES];

extern App   app;
extern Stage stage;

void initGift(int type)
{
	Entity *e;

	if (giftTextures[0] == NULL)
	{
		loadTextures();
	}

	e = spawnEntity();
	e->type = type;
	e->x = stage.player->x;
	e->y = stage.player->y;
	e->dy = -6;

	if (type == ET_GIFT)
	{
		e->texture = giftTextures[rand() % NUM_GIFT_TEXTURES];
	}
	else
	{
		e->texture = coalTextures[rand() % NUM_COAL_TEXTURES];
	}

	e->tick = tick;
	e->draw = draw;
}

static void tick(Entity *self)
{
	self->dy += 0.5 * app.deltaTime;

	self->y += self->dy * app.deltaTime;

	if (self->y + self->texture->rect.h >= GROUND_Y)
	{
		self->dead = 1;
	}
}

static void draw(Entity *self)
{
	blitAtlasImage(self->texture, self->x, self->y, 0, SDL_FLIP_NONE);
}

static void loadTextures(void)
{
	int  i;
	char filename[MAX_NAME_LENGTH];

	for (i = 0; i < NUM_GIFT_TEXTURES; i++)
	{
		sprintf(filename, "gfx/gift%02d.png", i + 1);
		giftTextures[i] = getAtlasImage(filename, 1);
	}

	for (i = 0; i < NUM_COAL_TEXTURES; i++)
	{
		sprintf(filename, "gfx/coal%02d.png", i + 1);
		coalTextures[i] = getAtlasImage(filename, 1);
	}
}
