/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/sound.h"
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

void initSnowmanHead(int x, int y)
{
	Entity      *e;
	SnowmanHead *s;

	if (texture == NULL)
	{
		texture = getAtlasImage("gfx/snowmanHead.png", 1);
	}

	s = malloc(sizeof(SnowmanHead));
	memset(s, 0, sizeof(SnowmanHead));
	s->thinkTime = FPS;
	s->startY = y;
	s->carrotTimer = rand() % (int)FPS * 3;

	e = spawnEntity();
	e->type = ET_SNOWMAN_HEAD;
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
	SnowmanHead *s;

	s = (SnowmanHead *)self->data;

	if (s->thinkTime > 0)
	{
		s->thinkTime = MAX(s->thinkTime - app.deltaTime, 0);

		if (s->thinkTime == 0)
		{
			self->dy = -(12 + rand() % 5);

			s->carrotTimer = rand() % (int)FPS * 3;

			playSound(SND_SNOWMAN_HEAD, CH_SNOWMAN);
		}
	}
	else
	{
		self->dy += 0.2 * app.deltaTime;

		self->y += self->dy * app.deltaTime;

		s->carrotTimer -= app.deltaTime;

		if (s->carrotTimer <= 0)
		{
			initCarrot(self->x, self->y);

			s->carrotTimer = rand() % (int)FPS;

			playSound(SND_CARROT, CH_CARROT);
		}

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

		for (i = 0; i < 50; i++)
		{
			addParticle(self->x, self->y, 235 + rand() % 20, 235 + rand() % 20, 255);
		}
	}
}
