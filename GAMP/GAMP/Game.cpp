#include "Game.h"
#include <iostream>

// Game 클래스 생성자
Game::Game()
    : window(nullptr), renderer(nullptr), isRunning(false), screenWidth(800), screenHeight(600), speed(5) {
    player = new GameObject(100, 100, true);
}

// Game 클래스 소멸자
Game::~Game() {
    delete player;
    cleanup();
}

// 게임 초기화
bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL 초기화 실패: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Hood Run - C++ Edition", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "윈도우 생성 실패: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "렌더러 생성 실패: " << SDL_GetError() << std::endl;
        return false;
    }

    // 기타 초기화 및 자원 로드
    loadResources();

    isRunning = true;
    return true;
}

// 자원 로드 함수
void Game::loadResources() {
    // 이미지, 사운드 등 필요한 자산 로드
}

// 게임 루프 실행
void Game::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();
    }
}

// 이벤트 처리
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // 추가 키보드, 마우스, 터치 이벤트 처리
    }
}

// 게임 업데이트
void Game::update() {
    // 게임 오브젝트 및 상태 업데이트
    updateObjects();
    updateBackground();
}

// 게임 렌더링
void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // 오브젝트 및 배경 그리기
    for (auto& object : objects) {
        object.render(renderer);
    }

    player->render(renderer);

    SDL_RenderPresent(renderer);
}

// 배경 업데이트
void Game::updateBackground() {
    // 배경을 스크롤하거나 업데이트하는 로직
}

// 오브젝트 업데이트
void Game::updateObjects() {
    for (auto& object : objects) {
        object.update();
    }
    player->update();
}

// 게임 자원 해제
void Game::cleanup() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

// 게임 변수 초기화
void Game::resetGameVariables() {
    // 점수, 상태, 속도 등 게임에 필요한 변수 초기화
}
