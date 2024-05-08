#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include <SDL.h>

// �� ĳ������ ���� ������
enum class EnemyState {
    Idle,
    Moving,
    Attacking,
    Dead
};

// �� ĳ���� Ŭ���� ����
class Enemy : public GameObject {
public:
    // �����ڿ� �Ҹ���
    Enemy(int x, int y);
    ~Enemy();

    // ������Ʈ �� ������ �Լ�
    void update() override;
    void render(SDL_Renderer* renderer) override;

    // ���� ���� �Լ�
    void startMoving();
    void startAttacking();
    void die();
    bool isDead() const;

private:
    // �� ĳ������ ���� �� �Ӽ�
    EnemyState state;
    int attackPower;
    int speed;

    // ���� ���� �Լ�
    void resetState();
    void handleCollisions();
};

#endif
