#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

enum class Direction {
    None,
    Up,
    Down,
    Left,
    Right
};

// 방향키 입력 처리를 위한 클래스
class Input {
public:
    Input();
    ~Input();

    // 방향키 입력 처리 함수
    void update();
    Direction getDirection() const;

private:
    Direction currentDirection;
};

#endif
