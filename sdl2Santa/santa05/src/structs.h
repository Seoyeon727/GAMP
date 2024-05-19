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
	int naughty;
} Chimney;

typedef struct
{
	int naughty;
} House;

typedef struct
{
	double  speed;
	Entity  entityHead, *entityTail;
	Entity *player;
} Stage;

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
