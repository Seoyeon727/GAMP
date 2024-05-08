#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>

// 게임 오브젝트의 기본 클래스
class GameObject {
public:
    GameObject(int x, int y, bool isPlayer = false);
    virtual void update();
    virtual void render(SDL_Renderer* renderer);
    // 충돌 검사를 위한 함수
    virtual bool collide(const GameObject& other);
    int x, y;
    bool isPlayer;
    bool isDead;
    bool isShield;
    bool isBooster;
    int speed;
};

// 게임의 핵심 클래스
class Game {
public:
    Game();
    ~Game();
    bool initialize();
    void run();
    void handleEvents();
    void update();
    void render();
    void cleanup();
    void resetGameVariables();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    int screenWidth;
    int screenHeight;
    int speed;
    std::vector<GameObject> objects;
    GameObject* player;
    void loadResources();
    void updateBackground();
    void updateObjects();
};

#endif
