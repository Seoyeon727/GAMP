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

// ����Ű �Է� ó���� ���� Ŭ����
class Input {
public:
    Input();
    ~Input();

    // ����Ű �Է� ó�� �Լ�
    void update();
    Direction getDirection() const;

private:
    Direction currentDirection;
};

#endif
