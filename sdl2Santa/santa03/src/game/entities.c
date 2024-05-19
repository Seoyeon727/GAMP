/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/util.h"
#include "entities.h"

extern App   app;
extern Stage stage;

void initEntities(void)
{
	memset(&stage.entityHead, 0, sizeof(Entity));
	stage.entityTail = &stage.entityHead;
}

void doEntities(void)
{
	Entity *e, *prev;

	prev = &stage.entityHead;

	for (e = stage.entityHead.next; e != NULL; e = e->next)
	{
		e->tick(e);

		if (e->dead)
		{
			if (e->die != NULL)
			{
				e->die(e);
			}

			prev->next = e->next;

			if (e == stage.entityTail)
			{
				stage.entityTail = prev;
			}

			if (e->data != NULL)
			{
				free(e->data);
			}

			free(e);

			e = prev;
		}

		prev = e;
	}
}

int canAddEntity(int x, int y, int w, int h)
{
	Entity *e;

	for (e = stage.entityHead.next; e != NULL; e = e->next)
	{
		if (collision(x, y, w, h, e->x, e->y, e->texture->rect.w, e->texture->rect.h))
		{
			return 0;
		}
	}

	return 1;
}

void drawEntities(void)
{
	Entity *e;

	for (e = stage.entityHead.next; e != NULL; e = e->next)
	{
		e->draw(e);
	}
}

Entity *spawnEntity(void)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));

	stage.entityTail->next = e;
	stage.entityTail = e;

	return e;
}
