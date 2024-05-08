#include "Game.h"
#include <iostream>

// Game Ŭ���� ������
Game::Game()
    : window(nullptr), renderer(nullptr), isRunning(false), screenWidth(800), screenHeight(600), speed(5) {
    player = new GameObject(100, 100, true);
}

// Game Ŭ���� �Ҹ���
Game::~Game() {
    delete player;
    cleanup();
}

// ���� �ʱ�ȭ
bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL �ʱ�ȭ ����: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Hood Run - C++ Edition", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "������ ���� ����: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "������ ���� ����: " << SDL_GetError() << std::endl;
        return false;
    }

    // ��Ÿ �ʱ�ȭ �� �ڿ� �ε�
    loadResources();

    isRunning = true;
    return true;
}

// �ڿ� �ε� �Լ�
void Game::loadResources() {
    // �̹���, ���� �� �ʿ��� �ڻ� �ε�
}

// ���� ���� ����
void Game::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();
    }
}

// �̺�Ʈ ó��
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // �߰� Ű����, ���콺, ��ġ �̺�Ʈ ó��
    }
}

// ���� ������Ʈ
void Game::update() {
    // ���� ������Ʈ �� ���� ������Ʈ
    updateObjects();
    updateBackground();
}

// ���� ������
void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // ������Ʈ �� ��� �׸���
    for (auto& object : objects) {
        object.render(renderer);
    }

    player->render(renderer);

    SDL_RenderPresent(renderer);
}

// ��� ������Ʈ
void Game::updateBackground() {
    // ����� ��ũ���ϰų� ������Ʈ�ϴ� ����
}

// ������Ʈ ������Ʈ
void Game::updateObjects() {
    for (auto& object : objects) {
        object.update();
    }
    player->update();
}

// ���� �ڿ� ����
void Game::cleanup() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

// ���� ���� �ʱ�ȭ
void Game::resetGameVariables() {
    // ����, ����, �ӵ� �� ���ӿ� �ʿ��� ���� �ʱ�ȭ
}
