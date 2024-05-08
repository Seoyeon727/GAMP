#include "Player.h"
#include <iostream>

// Player 생성자
Player::Player(int x, int y)
    : GameObject(x, y, true), state(PlayerState::Idle), jumpHeight(0), slideLength(0), speed(5), coins(0) {
}

// Player 소멸자
Player::~Player() {
    // 리소스 해제 로직이 필요한 경우 여기에 작성
}

// 업데이트 함수
void Player::update() {
    switch (state) {
    case PlayerState::Running:
        // 달리기 동작 처리
        x += speed;
        break;
    case PlayerState::Jumping:
        // 점프 동작 처리
        y -= jumpHeight;
        // 점프 이후 다시 러닝 상태로 돌아감
        state = PlayerState::Running;
        break;
    case PlayerState::Sliding:
        // 슬라이딩 동작 처리
        x += slideLength;
        // 슬라이딩 이후 다시 러닝 상태로 돌아감
        state = PlayerState::Running;
        break;
    case PlayerState::Dead:
        // 사망 상태 처리
        break;
    case PlayerState::Idle:
    default:
        // 기본적으로 움직임이 없는 상태
        break;
    }

    // 충돌 검사와 기타 상태 업데이트 로직
    handleCollisions();
}

// 렌더링 함수
void Player::render(SDL_Renderer* renderer) {
    // 플레이어를 화면에 그리기
    // SDL을 사용하여 필요한 그래픽을 그릴 수 있습니다.
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 예시로 빨간색 사각형 그리기
    SDL_Rect playerRect = { x, y, 50, 50 }; // 플레이어 사각형
    SDL_RenderFillRect(renderer, &playerRect);
}

// 상태 제어 함수
void Player::startRunning() {
    state = PlayerState::Running;
}

void Player::startJumping() {
    state = PlayerState::Jumping;
    jumpHeight = 10; // 임시로 점프 높이 설정
}

void Player::startSliding() {
    state = PlayerState::Sliding;
    slideLength = 20; // 임시로 슬라이딩 길이 설정
}

void Player::die() {
    state = PlayerState::Dead;
}

bool Player::isDead() const {
    return state == PlayerState::Dead;
}

// 내부 로직 함수
void Player::resetState() {
    state = PlayerState::Idle;
    jumpHeight = 0;
    slideLength = 0;
}

void Player::handleCollisions() {
    // 플레이어 충돌 검사 로직
    // 예: 다른 게임 오브젝트와의 충돌 여부 등을 판단
}
