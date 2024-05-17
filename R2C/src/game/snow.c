/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "snow.h"

#define MAX_SNOW 500

static Snow snow[MAX_SNOW];

extern App app;

void initSnow(void)
{
	Snow *s = NULL;
	int   i;

	for (i = 0; i < MAX_SNOW; i++)
	{
		s = &snow[i];

		memset(s, 0, sizeof(Snow));
		s->x = rand() % SCREEN_WIDTH;
		s->y = rand() % SCREEN_HEIGHT;
		s->dx = 1.0 * (rand() % 10 - rand() % 10) * 0.25;
		s->dy = 1.0 * (10 + rand() % 20) * 0.1;
		s->thinkTime = rand() % (int)FPS;
		s->size = 1 + rand() % 3;
	}
}

void doSnow(void)
{
	Snow *s = NULL;
	int   i;

	for (i = 0; i < MAX_SNOW; i++)
	{
		s = &snow[i];

		s->x += s->dx * app.deltaTime;

		if (s->x <= -s->size)
		{
			s->x = SCREEN_WIDTH;
		}

		if (s->x >= SCREEN_WIDTH)
		{
			s->x = 0;
		}

		s->y += s->dy * app.deltaTime;

		if (s->y >= GROUND_Y)
		{
			s->y = -s->size;
		}

		s->thinkTime -= app.deltaTime;

		if (s->thinkTime <= 0)
		{
			s->dx = 1.0 * (rand() % 10 - rand() % 10) * 0.25;

			s->thinkTime += FPS;
		}
	}
}

void drawSnow(void)
{
	Snow *s = NULL;
	int   i;

	for (i = 0; i < MAX_SNOW; i++)
	{
		s = &snow[i];

		drawRect(s->x, s->y, s->size, s->size, 255, 255, 255, 255);
	}
}
