/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define STRCPY(dest, src)             \
	strncpy(dest, src, sizeof(dest)); \
	dest[sizeof(dest) - 1] = '\0'
#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 900

#define FPS        60.0
#define LOGIC_RATE (FPS / 1000)

#define MAX_NAME_LENGTH     32
#define MAX_LINE_LENGTH     1024
#define MAX_FILENAME_LENGTH 1024

#define MAX_KEYBOARD_KEYS 350

#define MAX_SND_CHANNELS 16

#define GROUND_TILE_SIZE 64
#define GROUND_Y         (SCREEN_HEIGHT - GROUND_TILE_SIZE)

#define MAX_XMAS_SPIRIT 5

#define NUM_HIGHSCORES 10

enum
{
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_CENTER,
	TEXT_ALIGN_RIGHT
};

enum
{
	ET_NONE,
	ET_HOUSE,
	ET_CHIMNEY,
	ET_PLAYER,
	ET_GIFT,
	ET_COAL
};

enum
{
	SS_DEMO,
	SS_PLAYING,
	SS_GAME_OVER
};
