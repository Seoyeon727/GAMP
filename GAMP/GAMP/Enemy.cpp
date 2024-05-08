#include "Enemy.h"
#include <iostream>

// Enemy ������
Enemy::Enemy(int x, int y)
    : GameObject(x, y, false), state(EnemyState::Idle), attackPower(10), speed(3) {
}

// Enemy �Ҹ���
Enemy::~Enemy() {
    // ���ҽ� ���� ������ �ʿ��� ��� ���⿡ �ۼ�
}

// ������Ʈ �Լ�
void Enemy::update() {
    switch (state) {
    case EnemyState::Moving:
        // �̵� ���� ó��
        x -= speed; // ���� �������� �̵�
        break;
    case EnemyState::Attacking:
        // ���� ���� ó��
        std::cout << "���� ���� ���Դϴ�!" << std::endl;
        break;
    case EnemyState::Dead:
        // ��� ���� ó��
        break;
    case EnemyState::Idle:
    default:
        // �⺻������ �������� ���� ����
        break;
    }

    // �浹 �˻�� ��Ÿ ���� ������Ʈ ����
    handleCollisions();
}

// ������ �Լ�
void Enemy::render(SDL_Renderer* renderer) {
    // ���� ȭ�鿡 �׸���
    // SDL�� ����Ͽ� �ʿ��� �׷����� �׸� �� �ֽ��ϴ�.
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // ���÷� ��� �簢�� �׸���
    SDL_Rect enemyRect = { x, y, 50, 50 }; // �� �簢��
    SDL_RenderFillRect(renderer, &enemyRect);
}

// ���� ���� �Լ�
void Enemy::startMoving() {
    state = EnemyState::Moving;
}

void Enemy::startAttacking() {
    state = EnemyState::Attacking;
}

void Enemy::die() {
    state = EnemyState::Dead;
}

bool Enemy::isDead() const {
    return state == EnemyState::Dead;
}

// ���� ���� �Լ�
void Enemy::resetState() {
    state = EnemyState::Idle;
}

void Enemy::handleCollisions() {
    // �� ĳ������ �浹 �˻� ����
    // ��: �÷��̾� �Ǵ� ��ֹ����� �浹 ���� ���� �Ǵ�
}
