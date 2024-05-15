/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/sound.h"
#include "debris.h"
#include "entities.h"
#include "gift.h"
#include "player.h"

#define NUM_GIFT_TEXTURES 5
#define NUM_COAL_TEXTURES 4

static void tick(Entity *self);
static void move(Entity *self);
static void dropGift(void);
static void draw(Entity *self);
static void die(Entity *self);
static void loadTextures(void);

static AtlasImage *sleighTexture = NULL;
static AtlasImage *explosionTexture;
static AtlasImage *sleighPart1Texture, *sleighPart2Texture, *santaTexture;
static AtlasImage *giftTextures[NUM_GIFT_TEXTURES], *coalTextures[NUM_COAL_TEXTURES];

extern App   app;
extern Stage stage;

void initPlayer(void)
{
	Entity *e;
	Santa  *s;

	if (sleighTexture == NULL)
	{
		loadTextures();
	}

	s = malloc(sizeof(Santa));
	memset(s, 0, sizeof(Santa));

	e = spawnEntity();
	e->type = ET_PLAYER;
	e->x = 400;
	e->y = 200;
	e->dy = -8;
	e->texture = sleighTexture;
	e->data = s;

	e->tick = tick;
	e->draw = draw;
	e->die = die;

	stage.player = e;
}

static void tick(Entity *self)
{
	Santa *s;

	move(self);

	dropGift();

	s = (Santa *)stage.player->data;

	s->shudder = MAX(s->shudder - app.deltaTime, 0);
}

static void move(Entity *self)
{
	double dx;

	dx = 0;

	self->dy += 0.2 * app.deltaTime;

	if (app.keyboard[SDL_SCANCODE_W])
	{
		self->dy -= app.deltaTime;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		self->dy += app.deltaTime;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		dx = -4;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		dx = 4;
	}

	if (dx != 0)
	{
		self->dx += dx * app.deltaTime;
	}
	else
	{
		self->dx = 0;
	}

	self->dx = MAX(MIN(self->dx, 5), -5);
	self->dy = MAX(MIN(self->dy, 5), -5);

	self->x = MIN(MAX(10, self->x + self->dx * app.deltaTime), SCREEN_WIDTH - self->texture->rect.w - 10);

	self->y += self->dy * app.deltaTime;

	if (self->y < 50)
	{
		self->y = 50;
		self->dy = 0;
	}
	else if (self->y + self->texture->rect.h >= GROUND_Y)
	{
		self->y = GROUND_Y - self->texture->rect.h;
		self->dy = 0;
	}
}

static void dropGift(void)
{
	if (app.keyboard[SDL_SCANCODE_J] && stage.numGifts > 0)
	{
		stage.numGifts--;

		app.keyboard[SDL_SCANCODE_J] = 0;

		initGift(ET_GIFT);

		playSound(SND_THROW_GIFT, CH_SANTA);
	}

	if (app.keyboard[SDL_SCANCODE_L] && stage.numCoal > 0)
	{
		stage.numCoal--;

		app.keyboard[SDL_SCANCODE_L] = 0;

		initGift(ET_COAL);

		playSound(SND_THROW_GIFT, CH_SANTA);
	}
}

static void draw(Entity *self)
{
	Santa *s;
	int    x, y;

	s = (Santa *)stage.player->data;

	x = sin(s->shudder) * 5;
	y = -cos(s->shudder) * 3;

	blitAtlasImage(self->texture, self->x + x, self->y + y, 0, SDL_FLIP_NONE);

	if (self->dead)
	{
		blitAtlasImage(explosionTexture, s->hit.x + x, s->hit.y + y, 1, SDL_FLIP_NONE);
	}
}

static void die(Entity *self)
{
	int i;

	initDebris(self->x, self->y, sleighPart1Texture);
	initDebris(self->x, self->y, sleighPart2Texture);
	initDebris(self->x, self->y, santaTexture);

	for (i = 0; i < 6; i++)
	{
		if (rand() % 2 == 0)
		{
			initDebris(self->x, self->y, giftTextures[rand() % NUM_GIFT_TEXTURES]);
		}
		else
		{
			initDebris(self->x, self->y, coalTextures[rand() % NUM_COAL_TEXTURES]);
		}
	}

	stage.state = SS_GAME_OVER;

	stage.player = NULL;

	playSound(SND_GAME_OVER, CH_SANTA);
}

void killPlayer(int x, int y)
{
	Santa *s;

	s = (Santa *)stage.player->data;

	if (x > -1 && y > -1)
	{
		s->hit.x = x;
		s->hit.y = y;
	}
	else
	{
		s->hit.x = stage.player->x + (stage.player->texture->rect.w / 2);
		s->hit.y = stage.player->y + (stage.player->texture->rect.h / 2);
	}

	stage.pauseTimer = FPS / 2;

	stage.player->dead = 1;

	playSound(SND_SANTA_HIT, CH_SANTA);

	pauseMusic();
}

static void loadTextures(void)
{
	int  i;
	char filename[MAX_NAME_LENGTH];

	sleighTexture = getAtlasImage("gfx/sleigh.png", 1);

	explosionTexture = getAtlasImage("gfx/explosion.png", 1);
	sleighPart1Texture = getAtlasImage("gfx/sleighPart01.png", 1);
	sleighPart2Texture = getAtlasImage("gfx/sleighPart02.png", 1);
	santaTexture = getAtlasImage("gfx/santa.png", 1);

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
