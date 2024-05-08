#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>

// 게임 오브젝트의 기본 클래스
class GameObject {
public:
    // 생성자와 소멸자
    GameObject(int x, int y, bool isPlayer);
    virtual ~GameObject();

    // 업데이트 및 렌더링 함수
    virtual void update();
    virtual void render(SDL_Renderer* renderer);

    // 오브젝트의 속성
    int x, y;
    bool isPlayer;
    bool isDead;
    int speed;
};

#endif
