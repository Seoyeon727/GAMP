/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include <time.h>

#include "../common.h"

#include "../system/text.h"
#include "highscores.h"

static int highscoreComparator(const void *a, const void *b);

extern App   app;
extern Game  game;
extern Stage stage;

void initHighscores(void)
{
	char      *defaultNames[] = {"Dasher", "Dancer", "Prancer", "Vixen", "Comet", "Cupid", "Donner", "Blitzen", "Rudolph", "Sven"};
	int        i;
	Highscore *h;

	memset(&game.highscores, 0, sizeof(Highscore) * NUM_HIGHSCORES);


	qsort(game.highscores, NUM_HIGHSCORES, sizeof(Highscore), highscoreComparator);

	game.latestHighscore = NULL;
}

void drawHighScores(void)
{
	int        i, y, r, g, b;
	Highscore *h;
	char       text[16];

	app.fontScale = 1.25;

	drawShadowText("Highscores", SCREEN_WIDTH / 2, 50, 255, 255, 255, TEXT_ALIGN_CENTER);

	y = 130;

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		h = &game.highscores[i];

		r = g = b = 255;

		if (h == game.latestHighscore)
		{
			b = 0;
		}

		drawShadowText(h->name, 500, y, r, g, b, TEXT_ALIGN_LEFT);

		sprintf_s(text, "%06d", h->score);

		drawShadowText(text, SCREEN_WIDTH - 500, y, r, g, b, TEXT_ALIGN_RIGHT);

		y += 55;
	}

	app.fontScale = 1;
}

void addHighscore(void)
{
	Highscore *h;
	int        i;
	long       t;

	game.latestHighscore = NULL;

	if (stage.score > game.highscores[NUM_HIGHSCORES - 1].score)
	{
		h = &game.highscores[NUM_HIGHSCORES - 1];

		t = time(NULL);

		
		h->score = stage.score;
		h->time = t;

		qsort(game.highscores, NUM_HIGHSCORES, sizeof(Highscore), highscoreComparator);

		for (i = 0; i < NUM_HIGHSCORES; i++)
		{
			if (game.highscores[i].time == t)
			{
				game.latestHighscore = &game.highscores[i];
			}
		}
	}
}

static int highscoreComparator(const void *a, const void *b)
{
	Highscore *h1, *h2;
	int        result;

	h1 = ((Highscore *)a);
	h2 = ((Highscore *)b);

	result = h2->score - h1->score;

	if (result == 0)
	{
		return h1->time - h2->time;
	}

	return result;
}
