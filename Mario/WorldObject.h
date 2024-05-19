#ifndef WorldObject_H
#define WorldObject_H

#include "Size.h"
#include "Position.h"

struct SDL_Surface;

// ���� ������ ��� ������Ʈ���� �⺻ Ŭ����
class WorldObject
{
protected:
    Position position; // ��ġ
    Size size; // ũ��
    bool isWithinRangeOfCamera(int beginningOfCamera, int endOfCamera) const; // ī�޶� ���� ���� �ִ��� Ȯ���ϴ� �Լ�

public:
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    Position getPosition() const;
    virtual void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const = 0; // ���� ���� ������Ʈ�� �׸��� ���� ���� �Լ�
};

#endif // WorldObject_H