#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <SDL.h>

// 플레이어 상태 열거형
enum class PlayerState {
    Idle,
    Running,
    Jumping,
    Sliding,
    Dead
};

// 플레이어 클래스 정의
class Player : public GameObject {
public:
    // 생성자와 소멸자
    Player(int x, int y);
    ~Player();

    // 업데이트 및 렌더링 함수
    void update() override;
    void render(SDL_Renderer* renderer) override;

    // 상태 제어 함수
    void startRunning();
    void startJumping();
    void startSliding();
    void die();
    bool isDead() const;

private:
    // 플레이어의 상태 및 속성
    PlayerState state;
    int jumpHeight;
    int slideLength;
    int speed;
    int coins;

    // 내부 로직 함수
    void resetState();
    void handleCollisions();
};

#endif
