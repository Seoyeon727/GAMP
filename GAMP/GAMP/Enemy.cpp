#include "Enemy.h"
#include <iostream>

// Enemy 생성자
Enemy::Enemy(int x, int y)
    : GameObject(x, y, false), state(EnemyState::Idle), attackPower(10), speed(3) {
}

// Enemy 소멸자
Enemy::~Enemy() {
    // 리소스 해제 로직이 필요한 경우 여기에 작성
}

// 업데이트 함수
void Enemy::update() {
    switch (state) {
    case EnemyState::Moving:
        // 이동 동작 처리
        x -= speed; // 적이 왼쪽으로 이동
        break;
    case EnemyState::Attacking:
        // 공격 동작 처리
        std::cout << "적이 공격 중입니다!" << std::endl;
        break;
    case EnemyState::Dead:
        // 사망 상태 처리
        break;
    case EnemyState::Idle:
    default:
        // 기본적으로 움직임이 없는 상태
        break;
    }

    // 충돌 검사와 기타 상태 업데이트 로직
    handleCollisions();
}

// 렌더링 함수
void Enemy::render(SDL_Renderer* renderer) {
    // 적을 화면에 그리기
    // SDL을 사용하여 필요한 그래픽을 그릴 수 있습니다.
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // 예시로 녹색 사각형 그리기
    SDL_Rect enemyRect = { x, y, 50, 50 }; // 적 사각형
    SDL_RenderFillRect(renderer, &enemyRect);
}

// 상태 제어 함수
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

// 내부 로직 함수
void Enemy::resetState() {
    state = EnemyState::Idle;
}

void Enemy::handleCollisions() {
    // 적 캐릭터의 충돌 검사 로직
    // 예: 플레이어 또는 장애물과의 충돌 여부 등을 판단
}
