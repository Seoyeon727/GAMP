#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// 전역 변수
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
bool isRunning = true;

// 게임 초기화 함수
bool initialize() {
    // SDL 및 서브시스템 초기화
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL 초기화 실패: " << SDL_GetError() << std::endl;
        return false;
    }

    // 윈도우 생성
    window = SDL_CreateWindow("Hood Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "윈도우 생성 실패: " << SDL_GetError() << std::endl;
        return false;
    }

    // 렌더러 생성
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "렌더러 생성 실패: " << SDL_GetError() << std::endl;
        return false;
    }

    // SDL_Image 초기화
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_Image 초기화 실패: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

// 게임 로직 업데이트
void update() {
    // 게임 상태 업데이트 로직 추가
}

// 게임 화면 렌더링
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // 각종 UI 및 게임 요소 렌더링
    // ...

    SDL_RenderPresent(renderer);
}

// 이벤트 처리
void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // 추가 이벤트 로직
        // ...
    }
}

// 자원 해제
void cleanup() {
    // SDL 관련 자원 해제
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}

// 메인 함수
int main(int argc, char* argv[]) {
    if (!initialize()) {
        std::cerr << "게임 초기화 실패!" << std::endl;
        return -1;
    }

    // 게임 루프
    while (isRunning) {
        handleEvents();
        update();
        render();
    }

    cleanup();
    return 0;
}
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// 전역 변수
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
bool isRunning = true;

// 게임 초기화 함수
bool initialize() {
    // SDL 및 서브시스템 초기화
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL 초기화 실패: " << SDL_GetError() << std::endl;
        return false;
    }

    // 윈도우 생성
    window = SDL_CreateWindow("Hood Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "윈도우 생성 실패: " << SDL_GetError() << std::endl;
        return false;
    }

    // 렌더러 생성
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "렌더러 생성 실패: " << SDL_GetError() << std::endl;
        return false;
    }

    // SDL_Image 초기화
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_Image 초기화 실패: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

// 게임 로직 업데이트
void update() {
    // 게임 상태 업데이트 로직 추가
}

// 게임 화면 렌더링
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // 각종 UI 및 게임 요소 렌더링
    // ...

    SDL_RenderPresent(renderer);
}

// 이벤트 처리
void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // 추가 이벤트 로직
        // ...
    }
}

// 자원 해제
void cleanup() {
    // SDL 관련 자원 해제
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}

// 메인 함수
int main(int argc, char* argv[]) {
    if (!initialize()) {
        std::cerr << "게임 초기화 실패!" << std::endl;
        return -1;
    }

    // 게임 루프
    while (isRunning) {
        handleEvents();
        update();
        render();
    }

    cleanup();
    return 0;
}
