#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>

class GameObject {
public:
    // ������
    GameObject(int x, int y, bool isPlayer = false);

    // �Ҹ��� ����
    virtual ~GameObject();

    // ��� �Լ� ����
    virtual void update();
    virtual void render(SDL_Renderer* renderer);
    virtual bool collide(const GameObject& other);

    // ��� ����
    int x, y;
    bool isPlayer;
    bool isDead;
    bool isShield;
    bool isBooster;
    int speed;
};

#endif

