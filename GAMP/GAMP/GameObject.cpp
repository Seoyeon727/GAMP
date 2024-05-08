#include "GameObject.h"

// GameObject 생성자
GameObject::GameObject(int x, int y, bool isPlayer)
    : x(x), y(y), isPlayer(isPlayer), isDead(false), speed(5) {
}

// GameObject 소멸자
GameObject::~GameObject() {
    // 리소스 해제 로직이 필요한 경우 여기에 작성
}

// 업데이트 함수
void GameObject::update() {
    // 오브젝트의 상태를 업데이트
    x += speed; // 예시로 오른쪽으로 이동
}

// 렌더링 함수
void GameObject::render(SDL_Renderer* renderer) {
    // 기본 오브젝트를 그리기 위한 로직
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // 흰색 사각형 그리기
    SDL_Rect objectRect = { x, y, 50, 50 }; // 기본 크기 사각형
    SDL_RenderFillRect(renderer, &objectRect);
}
