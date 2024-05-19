/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

typedef struct AtlasImage AtlasImage;
typedef struct Texture    Texture;
typedef struct Entity     Entity;
typedef struct Quadtree   Quadtree;
typedef struct Particle   Particle;

struct Texture
{
	char         name[MAX_FILENAME_LENGTH];
	SDL_Texture *texture = NULL;
	Texture     *next = NULL;
};

struct AtlasImage
{
	char         filename[MAX_FILENAME_LENGTH];
	SDL_Texture *texture = NULL;
	SDL_Rect     rect;
	int          rotated;
	AtlasImage  *next = NULL;
};

struct Entity
{
	int         type;
	double      x, y;
	double      dx, dy;
	AtlasImage *texture = NULL;
	int         dead;
	void(*data);
	void (*tick)(Entity *self);
	void (*draw)(Entity *self);
	void (*touch)(Entity *self, Entity *other);
	void (*die)(Entity *self);
	Entity *next = NULL;
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
	double   successLights;
	int      naughty;
	Chimney *chimney = NULL;
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

struct Particle
{
	double    x, y;
	double    dx, dy;
	double    life;
	SDL_Color color;
	Particle *next = NULL;
};

typedef struct
{
	double      x, y;
	double      speed;
	AtlasImage *texture = NULL;
} Tree;

typedef struct
{
	double    startX;
	int       heights[HILLS_HEIGHT_LENGTH];
	int       numTrees;
	Tree      trees[MAX_HILL_TREES];
	int       y;
	int       amplitude;
	double    period;
	double    speed;
	SDL_Color color;
} Hills;

struct Quadtree
{
	int       depth;
	int       x, y, w, h;
	Entity  **ents;
	int       capacity;
	int       numEnts;
	int       addedTo;
	Quadtree *node[4];
};

typedef struct
{
	double   speed;
	int      score;
	int      xmasSpirit;
	int      numGifts;
	int      numCoal;
	int      state;
	Quadtree quadtree;
	Entity   entityHead, *entityTail;
	Entity  *player = NULL;
	double   pauseTimer;
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
	Highscore *latestHighscore = NULL;
} Game;

typedef struct
{
	struct
	{
		void (*logic)(void);
		void (*draw)(void);
	} delegate;
	double        deltaTime;
	SDL_Renderer *renderer = NULL;
	SDL_Window   *window = NULL;
	int           keyboard[MAX_KEYBOARD_KEYS];
	double        fontScale;
} App;
