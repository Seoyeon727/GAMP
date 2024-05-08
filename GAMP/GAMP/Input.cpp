#include "Input.h"

// Input 클래스 생성자
Input::Input() : currentDirection(Direction::None) {}

// Input 클래스 소멸자
Input::~Input() {}

// 방향키 입력을 업데이트하는 함수
void Input::update() {
    SDL_Event event;
    currentDirection = Direction::None;

    // 모든 이벤트를 처리
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            currentDirection = Direction::None;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_UP:
                currentDirection = Direction::Up;
                break;
            case SDLK_DOWN:
                currentDirection = Direction::Down;
                break;
            case SDLK_LEFT:
                currentDirection = Direction::Left;
                break;
            case SDLK_RIGHT:
                currentDirection = Direction::Right;
                break;
            default:
                currentDirection = Direction::None;
                break;
            }
        }
    }
}

// 현재 방향키 입력 방향을 반환하는 함수
Direction Input::getDirection() const {
    return currentDirection;
}
