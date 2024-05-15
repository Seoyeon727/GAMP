/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/sound.h"
#include "entities.h"
#include "particles.h"
#include "player.h"
#include "snowball.h"

static void tick(Entity *self);
static void draw(Entity *self);
static void touch(Entity *self, Entity *other);

static AtlasImage *texture = NULL;

extern App   app;
extern Stage stage;

void initSnowball(int x, int y)
{
	Entity   *e;
	Snowball *s;

	if (texture == NULL)
	{
		texture = getAtlasImage("gfx/snowball.png", 1);
	}

	s = malloc(sizeof(Snowball));
	memset(s, 0, sizeof(Snowball));
	s->thinkTime = FPS;
	s->startY = y;

	e = spawnEntity();
	e->type = ET_SNOWBALL;
	e->x = x;
	e->y = y;
	e->texture = texture;
	e->tick = tick;
	e->draw = draw;
	e->touch = touch;

	e->data = s;
}

static void tick(Entity *self)
{
	Snowball *s;

	s = (Snowball *)self->data;

	if (s->thinkTime > 0)
	{
		s->thinkTime = MAX(s->thinkTime - app.deltaTime, 0);

		if (s->thinkTime == 0)
		{
			self->dy = -(12 + rand() % 5);
		}
	}
	else
	{
		self->dy += 0.2 * app.deltaTime;

		self->y += self->dy * app.deltaTime;

		if (self->y > s->startY)
		{
			self->y = s->startY;

			s->thinkTime = FPS + rand() % (int)FPS;

			playSound(SND_SNOWMAN_CATCH, CH_SNOWMAN);
		}
	}

	self->x -= stage.speed * app.deltaTime;

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
			addParticle(self->x, self->y, 235 + rand() % 20, 235 + rand() % 20, 255);
		}
	}
}
