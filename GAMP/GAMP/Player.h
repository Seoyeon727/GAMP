#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <SDL.h>

// �÷��̾� ���� ������
enum class PlayerState {
    Idle,
    Running,
    Jumping,
    Sliding,
    Dead
};

// �÷��̾� Ŭ���� ����
class Player : public GameObject {
public:
    // �����ڿ� �Ҹ���
    Player(int x, int y);
    ~Player();

    // ������Ʈ �� ������ �Լ�
    void update() override;
    void render(SDL_Renderer* renderer) override;

    // ���� ���� �Լ�
    void startRunning();
    void startJumping();
    void startSliding();
    void die();
    bool isDead() const;

private:
    // �÷��̾��� ���� �� �Ӽ�
    PlayerState state;
    int jumpHeight;
    int slideLength;
    int speed;
    int coins;

    // ���� ���� �Լ�
    void resetState();
    void handleCollisions();
};

#endif
