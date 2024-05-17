/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/sound.h"
#include "../system/text.h"
#include "chimney.h"
#include "entities.h"
#include "particles.h"
#include "player.h"

#define NUM_CHIMNEY_TEXTURES 4

static void tick(Entity *self);
static void draw(Entity *self);
static void touch(Entity *self, Entity *other);
static void die(Entity *self);
static void loadTextures(void);

static AtlasImage *chimneyTextures[NUM_CHIMNEY_TEXTURES] = {NULL};
static AtlasImage *cleanChimneyTexture;

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
	e->touch = touch;
	e->die = die;

	e->data = c;

	return e;
}

static void tick(Entity *self)
{
	Chimney *c;

	c = (Chimney *)self->data;

	c->pointsY = MAX(c->pointsY - app.deltaTime, self->y - 50);
	c->pointsLife = MAX(c->pointsLife - app.deltaTime, 0);
	c->shudder = MAX(c->shudder - app.deltaTime, 0);

	self->x -= stage.speed * app.deltaTime;

	self->dead = self->x < -self->texture->rect.w;
}

static void draw(Entity *self)
{
	Chimney *c;
	char     pointsText[5];
	int      x, g, b;

	c = (Chimney *)self->data;

	if (!c->complete)
	{
		blitAtlasImage(self->texture, self->x, self->y, 0, SDL_FLIP_NONE);
	}
	else
	{
		x = sin(c->shudder) * 5;

		blitAtlasImage(cleanChimneyTexture, self->x + x, self->y, 0, SDL_FLIP_NONE);
	}

	if (c->points != 0 && c->pointsLife > 0)
	{
		sprintf(pointsText, "%d", c->points);

		g = b = c->points > 0 ? 255 : 0;

		drawText(pointsText, self->x + (self->texture->rect.w / 2), c->pointsY, 255, g, b, TEXT_ALIGN_CENTER, 0);
	}
}

static void touch(Entity *self, Entity *other)
{
	Chimney *c;
	int      i, score;

	if (other->type == ET_GIFT || other->type == ET_COAL)
	{
		c = (Chimney *)self->data;

		score = 0;

		if ((!c->naughty && other->type == ET_GIFT) || (c->naughty && other->type == ET_COAL))
		{
			if (!c->complete)
			{
				score = 100;

				for (i = 0; i < 25; i++)
				{
					addParticle(self->x, self->y, 235 + rand() % 20, 235 + rand() % 20, 255);
				}

				if (!c->naughty)
				{
					playSound(SND_CHIMNEY_COMPLETE, CH_CHIMNEY);
				}
			}
			else
			{
				score = 25;
			}
		}
		else
		{
			score = -100;
		}

		stage.score += score;

		c->complete = 1;
		c->shudder = FPS / 2;
		c->points += score;
		c->pointsY = self->y - 25;
		c->pointsLife = FPS * 2;

		other->dead = 1;

		playSound(SND_CHIMNEY_ENTER, CH_GIFT);
	}
	else if (other == stage.player)
	{
		killPlayer(-1, -1);
	}
}

static void die(Entity *self)
{
	Chimney *c;

	c = (Chimney *)self->data;

	if (!c->complete && !c->naughty)
	{
		stage.xmasSpirit = MAX(stage.xmasSpirit - 1, 0);

		if (stage.player != NULL)
		{
			((Santa *)stage.player->data)->shudder = FPS / 2;

			playSound(SND_SANTA_OUCH, CH_SANTA);
		}
	}
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

	cleanChimneyTexture = getAtlasImage("gfx/cleanChimney.png", 1);
}
