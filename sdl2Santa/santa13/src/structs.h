/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

typedef struct AtlasImage AtlasImage;
typedef struct Texture    Texture;
typedef struct Entity     Entity;

struct Texture
{
	char         name[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	Texture     *next;
};

struct AtlasImage
{
	char         filename[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	SDL_Rect     rect;
	int          rotated;
	AtlasImage  *next;
};

struct Entity
{
	int         type;
	double      x, y;
	double      dx, dy;
	AtlasImage *texture;
	int         dead;
	void(*data);
	void (*tick)(Entity *self);
	void (*draw)(Entity *self);
	void (*touch)(Entity *self, Entity *other);
	void (*die)(Entity *self);
	Entity *next;
};

typedef struct
{
	SDL_Point hit;
	double    shudder;
} Santa;

typedef struct
{
	int    complete;
	int    naughty;
	int    points;
	double pointsY;
	double pointsLife;
	double shudder;
} Chimney;

typedef struct
{
	int naughty;
} House;

typedef struct
{
	int    startY;
	double bob;
	double speed;
} Sack;

typedef struct
{
	double thinkTime;
	int    startY;
} Snowball;

typedef struct
{
	double thinkTime;
	int    startY;
	double carrotTimer;
} SnowmanHead;

typedef struct
{
	double x, y;
	double dx, dy;
	double thinkTime;
	int    size;
} Snow;

typedef struct
{
	double  speed;
	int     score;
	int     xmasSpirit;
	int     numGifts;
	int     numCoal;
	int     state;
	Entity  entityHead, *entityTail;
	Entity *player;
	double  pauseTimer;
} Stage;

typedef struct
{
	char name[MAX_NAME_LENGTH];
	int  score;
	long time;
} Highscore;

typedef struct
{
	Highscore  highscores[NUM_HIGHSCORES];
	Highscore *latestHighscore;
} Game;

typedef struct
{
	struct
	{
		void (*logic)(void);
		void (*draw)(void);
	} delegate;
	double        deltaTime;
	SDL_Renderer *renderer;
	SDL_Window   *window;
	int           keyboard[MAX_KEYBOARD_KEYS];
	double        fontScale;
} App;
