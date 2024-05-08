#include "Player.h"
#include <iostream>

// Player ������
Player::Player(int x, int y)
    : GameObject(x, y, true), state(PlayerState::Idle), jumpHeight(0), slideLength(0), speed(5), coins(0) {
}

// Player �Ҹ���
Player::~Player() {
    // ���ҽ� ���� ������ �ʿ��� ��� ���⿡ �ۼ�
}

// ������Ʈ �Լ�
void Player::update() {
    switch (state) {
    case PlayerState::Running:
        // �޸��� ���� ó��
        x += speed;
        break;
    case PlayerState::Jumping:
        // ���� ���� ó��
        y -= jumpHeight;
        // ���� ���� �ٽ� ���� ���·� ���ư�
        state = PlayerState::Running;
        break;
    case PlayerState::Sliding:
        // �����̵� ���� ó��
        x += slideLength;
        // �����̵� ���� �ٽ� ���� ���·� ���ư�
        state = PlayerState::Running;
        break;
    case PlayerState::Dead:
        // ��� ���� ó��
        break;
    case PlayerState::Idle:
    default:
        // �⺻������ �������� ���� ����
        break;
    }

    // �浹 �˻�� ��Ÿ ���� ������Ʈ ����
    handleCollisions();
}

// ������ �Լ�
void Player::render(SDL_Renderer* renderer) {
    // �÷��̾ ȭ�鿡 �׸���
    // SDL�� ����Ͽ� �ʿ��� �׷����� �׸� �� �ֽ��ϴ�.
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // ���÷� ������ �簢�� �׸���
    SDL_Rect playerRect = { x, y, 50, 50 }; // �÷��̾� �簢��
    SDL_RenderFillRect(renderer, &playerRect);
}

// ���� ���� �Լ�
void Player::startRunning() {
    state = PlayerState::Running;
}

void Player::startJumping() {
    state = PlayerState::Jumping;
    jumpHeight = 10; // �ӽ÷� ���� ���� ����
}

void Player::startSliding() {
    state = PlayerState::Sliding;
    slideLength = 20; // �ӽ÷� �����̵� ���� ����
}

void Player::die() {
    state = PlayerState::Dead;
}

bool Player::isDead() const {
    return state == PlayerState::Dead;
}

// ���� ���� �Լ�
void Player::resetState() {
    state = PlayerState::Idle;
    jumpHeight = 0;
    slideLength = 0;
}

void Player::handleCollisions() {
    // �÷��̾� �浹 �˻� ����
    // ��: �ٸ� ���� ������Ʈ���� �浹 ���� ���� �Ǵ�
}
