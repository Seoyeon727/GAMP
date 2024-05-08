#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>

// ���� ������Ʈ�� �⺻ Ŭ����
class GameObject {
public:
    // �����ڿ� �Ҹ���
    GameObject(int x, int y, bool isPlayer);
    virtual ~GameObject();

    // ������Ʈ �� ������ �Լ�
    virtual void update();
    virtual void render(SDL_Renderer* renderer);

    // ������Ʈ�� �Ӽ�
    int x, y;
    bool isPlayer;
    bool isDead;
    int speed;
};

#endif
