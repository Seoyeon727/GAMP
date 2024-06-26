/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include <SDL2/SDL_image.h>

#include "../common.h"

extern App app;

static Texture  textureHead;
static Texture *textureTail = NULL;

void initTextures(void)
{
	memset(&textureHead, 0, sizeof(Texture));

	textureTail = &textureHead;
}

static SDL_Texture *getTexture(char *name)
{
	Texture *t = NULL;

	for (t = textureHead.next; t != NULL; t = t->next)
	{
		if (strcmp(t->name, name) == 0)
		{
			return t->texture;
		}
	}

	return NULL;
}

static void addTextureToCache(char *name, SDL_Texture *sdlTexture)
{
	Texture *texture = NULL;

	texture = malloc(sizeof(Texture));
	memset(texture, 0, sizeof(Texture));
	textureTail->next = texture;
	textureTail = texture;

	
	texture->texture = sdlTexture;
}

SDL_Texture *toTexture(SDL_Surface *surface, int destroySurface)
{
	SDL_Texture *texture = NULL;

	texture = SDL_CreateTextureFromSurface(app.renderer, surface);

	if (destroySurface)
	{
		SDL_FreeSurface(surface);
	}

	return texture;
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture = NULL;

	texture = getTexture(filename);

	if (texture == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s ...", filename);
		texture = IMG_LoadTexture(app.renderer, filename);
		addTextureToCache(filename, texture);
	}

	return texture;
}
