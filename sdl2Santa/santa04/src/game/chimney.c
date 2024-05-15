/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "chimney.h"
#include "entities.h"

#define NUM_CHIMNEY_TEXTURES 4

static void tick(Entity *self);
static void draw(Entity *self);
static void loadTextures(void);

static AtlasImage *chimneyTextures[NUM_CHIMNEY_TEXTURES] = {NULL};

extern App   app;
extern Stage stage;

Entity *initChimney(int naughty)
{
	Entity  *e;
	Chimney *c;

	if (chimneyTextures[0] == NULL)
	{
		loadTextures();
	}

	c = malloc(sizeof(Chimney));
	memset(c, 0, sizeof(Chimney));
	c->naughty = naughty;

	e = spawnEntity();
	e->type = ET_CHIMNEY;
	e->texture = chimneyTextures[rand() % NUM_CHIMNEY_TEXTURES];
	e->tick = tick;
	e->draw = draw;

	e->data = c;

	return e;
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

static void loadTextures(void)
{
	int  i;
	char filename[MAX_NAME_LENGTH];

	for (i = 0; i < NUM_CHIMNEY_TEXTURES; i++)
	{
		sprintf(filename, "gfx/chimney%02d.png", i + 1);
		chimneyTextures[i] = getAtlasImage(filename, 1);
	}
}
