#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>

class GameObject {
public:
    // 생성자
    GameObject(int x, int y, bool isPlayer = false);

    // 소멸자 선언
    virtual ~GameObject();

    // 멤버 함수 선언
    virtual void update();
    virtual void render(SDL_Renderer* renderer);
    virtual bool collide(const GameObject& other);

    // 멤버 변수
    int x, y;
    bool isPlayer;
    bool isDead;
    bool isShield;
    bool isBooster;
    int speed;
};

#endif

