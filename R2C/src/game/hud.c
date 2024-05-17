/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "../system/text.h"

#define XMAS_SPIRIT_BAR_WIDTH 200

static double score;
static double xmasSpirit;
static double xmaxSpiritBarShudder;
static double xmaxSpiritBarWarningTimer;

extern App   app;
extern Stage stage;

void initHUD(void)
{
	score = 0;

	xmasSpirit = stage.xmasSpirit;

	xmaxSpiritBarShudder = 0;

	xmaxSpiritBarWarningTimer = 0;
}

void doHUD(void)
{
	if (score < stage.score)
	{
		score = MIN(score + 2 * app.deltaTime, stage.score);
	}
	else
	{
		score = stage.score;
	}

	if (xmasSpirit > stage.xmasSpirit)
	{
		xmasSpirit = MAX(xmasSpirit - (0.05 * app.deltaTime), stage.xmasSpirit);

		xmaxSpiritBarShudder += app.deltaTime;
	}
	else
	{
		xmaxSpiritBarShudder = 0;
	}

	xmaxSpiritBarWarningTimer += app.deltaTime;
}

void drawHUD(void)
{
	char text[64];
	int  w, y, r, g, b;

	sprintf(text, "Score: %06d", (int)score);
	drawText(text, 10, 0, 255, 255, 255, TEXT_ALIGN_LEFT, 0);

	sprintf(text, "Gifts: %d", stage.numGifts);
	drawText(text, 500, 0, 255, 255, 255, TEXT_ALIGN_LEFT, 0);

	sprintf(text, "Coal: %d", stage.numCoal);
	drawText(text, 850, 0, 255, 255, 255, TEXT_ALIGN_LEFT, 0);

	sprintf(text, "Xmas Spirit:");
	drawText(text, SCREEN_WIDTH - (XMAS_SPIRIT_BAR_WIDTH + 20), 0, 255, 255, 255, TEXT_ALIGN_RIGHT, 0);

	y = 11 + (sin(xmaxSpiritBarShudder) * 5);

	drawOutlineRect(SCREEN_WIDTH - (XMAS_SPIRIT_BAR_WIDTH + 10), y, XMAS_SPIRIT_BAR_WIDTH, 24, 255, 255, 255, 255);

	w = XMAS_SPIRIT_BAR_WIDTH - 4;
	w = MAX(w * (xmasSpirit / MAX_XMAS_SPIRIT), 0);

	r = 160;
	g = 192;
	b = 255;

	if (xmasSpirit <= 1 && (int)xmaxSpiritBarWarningTimer % (int)FPS < FPS / 2)
	{
		r = g = b = 255;
	}

	drawRect(SCREEN_WIDTH - (XMAS_SPIRIT_BAR_WIDTH + 10) + 2, y + 2, w, 20, r, g, b, 255);
}
