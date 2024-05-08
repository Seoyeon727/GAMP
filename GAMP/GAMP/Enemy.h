#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include <SDL.h>

// 적 캐릭터의 상태 열거형
enum class EnemyState {
    Idle,
    Moving,
    Attacking,
    Dead
};

// 적 캐릭터 클래스 정의
class Enemy : public GameObject {
public:
    // 생성자와 소멸자
    Enemy(int x, int y);
    ~Enemy();

    // 업데이트 및 렌더링 함수
    void update() override;
    void render(SDL_Renderer* renderer) override;

    // 상태 제어 함수
    void startMoving();
    void startAttacking();
    void die();
    bool isDead() const;

private:
    // 적 캐릭터의 상태 및 속성
    EnemyState state;
    int attackPower;
    int speed;

    // 내부 로직 함수
    void resetState();
    void handleCollisions();
};

#endif
