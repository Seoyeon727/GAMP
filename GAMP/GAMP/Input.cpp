#include "Input.h"

// Input Ŭ���� ������
Input::Input() : currentDirection(Direction::None) {}

// Input Ŭ���� �Ҹ���
Input::~Input() {}

// ����Ű �Է��� ������Ʈ�ϴ� �Լ�
void Input::update() {
    SDL_Event event;
    currentDirection = Direction::None;

    // ��� �̺�Ʈ�� ó��
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

// ���� ����Ű �Է� ������ ��ȯ�ϴ� �Լ�
Direction Input::getDirection() const {
    return currentDirection;
}
