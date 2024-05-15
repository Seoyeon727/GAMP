/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "chimney.h"
#include "entities.h"
#include "house.h"
#include "player.h"

#define NUM_HOUSE_TEXTURES 9

static void tick(Entity *self);
static void draw(Entity *self);
static void touch(Entity *self, Entity *other);
static void loadTextures(void);

static AtlasImage *houseTextures[NUM_HOUSE_TEXTURES] = {NULL};
static AtlasImage *houseLights;

extern App   app;
extern Stage stage;

void initHouse(void)
{
	Entity *e, *chimney;
	House  *h;
	int     x, y;

	if (houseTextures[0] == NULL)
	{
		loadTextures();
	}

	x = SCREEN_WIDTH;
	y = GROUND_Y - houseTextures[0]->rect.h;

	if (canAddEntity(x, y, houseTextures[0]->rect.w, houseTextures[0]->rect.h))
	{
		h = malloc(sizeof(House));
		memset(h, 0, sizeof(House));
		h->naughty = rand() % 2;

		chimney = initChimney(h->naughty);

		e = spawnEntity();
		e->type = ET_HOUSE;
		e->x = x;
		e->y = y;
		e->texture = houseTextures[rand() % NUM_HOUSE_TEXTURES];
		e->data = h;

		e->tick = tick;
		e->draw = draw;
		e->touch = touch;

		chimney->x = x + ((e->texture->rect.w - chimney->texture->rect.w) / 2);
		chimney->y = e->y - 30;

		x = rand() % 70 - rand() % 70;
		chimney->x += x;
		chimney->y += abs(x * 0.75);
	}
}

static void tick(Entity *self)
{
	self->x -= stage.speed * app.deltaTime;

	self->dead = self->x < -self->texture->rect.w;
}

static void draw(Entity *self)
{
	House *h;

	h = (House *)self->data;

	blitAtlasImage(self->texture, self->x, self->y, 0, SDL_FLIP_NONE);

	if (h->naughty)
	{
		blitAtlasImage(houseLights, self->x, self->y, 0, SDL_FLIP_NONE);
	}
}

static void touch(Entity *self, Entity *other)
{
	if (other == stage.player)
	{
		killPlayer(-1, -1);
	}
}

static void loadTextures(void)
{
	int  i;
	char filename[MAX_NAME_LENGTH];

	for (i = 0; i < NUM_HOUSE_TEXTURES; i++)
	{
		sprintf(filename, "gfx/house%02d.png", i + 1);
		houseTextures[i] = getAtlasImage(filename, 1);
	}

	houseLights = getAtlasImage("gfx/houseLights.png", 1);
}
