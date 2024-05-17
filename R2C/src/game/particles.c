/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/draw.h"
#include "particles.h"

static Particle head, *tail;

extern App   app;
extern Stage stage;

void initParticles(void)
{
	memset(&head, 0, sizeof(Particle));

	tail = &head;
}

void doParticles(void)
{
	Particle *p, *prev;

	prev = &head;

	for (p = head.next; p != NULL; p = p->next)
	{
		p->x += p->dx * app.deltaTime;
		p->y += p->dy * app.deltaTime;

		p->x -= stage.speed * app.deltaTime;

		p->life -= app.deltaTime;

		if (p->life <= 0)
		{
			prev->next = p->next;

			if (p == tail)
			{
				tail = prev;
			}

			free(p);

			p = prev;
		}

		prev = p;
	}
}

void drawParticles(void)
{
	Particle *p;

	for (p = head.next; p != NULL; p = p->next)
	{
		drawRect(p->x - 1, p->y - 1, 3, 3, p->color.r, p->color.g, p->color.b, p->color.a);
	}
}

void addParticle(int x, int y, int r, int g, int b)
{
	Particle *p;

	p = malloc(sizeof(Particle));
	memset(p, 0, sizeof(Particle));
	tail->next = p;
	tail = p;

	p->x = x;
	p->y = y;
	p->dx = 1.0 * (rand() % 25 - rand() % 25) * 0.1;
	p->dy = 1.0 * (rand() % 25 - rand() % 25) * 0.1;
	p->life = FPS / 2 + (rand() % (int)FPS);
	p->color.r = r;
	p->color.g = g;
	p->color.b = b;
	p->color.a = 255;
}

void clearParticles(void)
{
	Particle *p;

	while (head.next)
	{
		p = head.next;

		head.next = p->next;

		free(p);
	}
}
