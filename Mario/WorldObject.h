#ifndef WorldObject_H
#define WorldObject_H

#include "Size.h"
#include "Position.h"

struct SDL_Surface;

// 게임 세계의 모든 오브젝트들의 기본 클래스
class WorldObject
{
protected:
    Position position; // 위치
    Size size; // 크기
    bool isWithinRangeOfCamera(int beginningOfCamera, int endOfCamera) const; // 카메라 범위 내에 있는지 확인하는 함수

public:
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    Position getPosition() const;
    virtual void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const = 0; // 세계 안의 오브젝트를 그리는 순수 가상 함수
};

#endif // WorldObject_H