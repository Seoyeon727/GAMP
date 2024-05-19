/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

void initQuadtree(Quadtree *root);
void addToQuadtree(Entity *e, Quadtree *root);
void removeFromQuadtree(Entity *e, Quadtree *root);
void getAllEntsWithin(int x, int y, int w, int h, Entity **candidates);
void destroyQuadtree(Quadtree *root);
