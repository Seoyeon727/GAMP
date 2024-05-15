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

#define MAX_QT_CANDIDATES 1024

#define NUM_HIGHSCORES 10

#define HILL_WIDTH          8
#define HILLS_HEIGHT_LENGTH (SCREEN_WIDTH / HILL_WIDTH)
#define MAX_HILL_TREES      48

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
	ET_COAL,
	ET_GIFT_SACK,
	ET_COAL_SACK,
	ET_SNOWMAN,
	ET_SNOWBALL,
	ET_HEADLESS_SNOWMAN,
	ET_SNOWMAN_HEAD,
	ET_CARROT
};

enum
{
	SS_DEMO,
	SS_PLAYING,
	SS_GAME_OVER
};

enum
{
	SND_THROW_GIFT,
	SND_CHIMNEY_COMPLETE,
	SND_GAME_OVER,
	SND_SNOWMAN_HEAD,
	SND_CARROT,
	SND_SNOWMAN_CATCH,
	SND_SANTA_HIT,
	SND_CHIMNEY_ENTER,
	SND_SACK_APPEAR,
	SND_GIFT_SACK,
	SND_COAL_SACK,
	SND_GIFT_BREAK,
	SND_SANTA_OUCH,
	SND_MAX
};

enum
{
	CH_ANY = -1,
	CH_SANTA,
	CH_CHIMNEY,
	CH_SNOWMAN,
	CH_CARROT,
	CH_GIFT,
	CH_SACK
};
