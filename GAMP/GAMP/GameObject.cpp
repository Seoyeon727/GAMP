#include "GameObject.h"

// GameObject ������
GameObject::GameObject(int x, int y, bool isPlayer)
    : x(x), y(y), isPlayer(isPlayer), isDead(false), speed(5) {
}

// GameObject �Ҹ���
GameObject::~GameObject() {
    // ���ҽ� ���� ������ �ʿ��� ��� ���⿡ �ۼ�
}

// ������Ʈ �Լ�
void GameObject::update() {
    // ������Ʈ�� ���¸� ������Ʈ
    x += speed; // ���÷� ���������� �̵�
}

// ������ �Լ�
void GameObject::render(SDL_Renderer* renderer) {
    // �⺻ ������Ʈ�� �׸��� ���� ����
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // ��� �簢�� �׸���
    SDL_Rect objectRect = { x, y, 50, 50 }; // �⺻ ũ�� �簢��
    SDL_RenderFillRect(renderer, &objectRect);
}
