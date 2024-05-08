#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// ���� ����
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
bool isRunning = true;

// ���� �ʱ�ȭ �Լ�
bool initialize() {
    // SDL �� ����ý��� �ʱ�ȭ
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL �ʱ�ȭ ����: " << SDL_GetError() << std::endl;
        return false;
    }

    // ������ ����
    window = SDL_CreateWindow("Hood Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "������ ���� ����: " << SDL_GetError() << std::endl;
        return false;
    }

    // ������ ����
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "������ ���� ����: " << SDL_GetError() << std::endl;
        return false;
    }

    // SDL_Image �ʱ�ȭ
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_Image �ʱ�ȭ ����: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

// ���� ���� ������Ʈ
void update() {
    // ���� ���� ������Ʈ ���� �߰�
}

// ���� ȭ�� ������
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // ���� UI �� ���� ��� ������
    // ...

    SDL_RenderPresent(renderer);
}

// �̺�Ʈ ó��
void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // �߰� �̺�Ʈ ����
        // ...
    }
}

// �ڿ� ����
void cleanup() {
    // SDL ���� �ڿ� ����
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}

// ���� �Լ�
int main(int argc, char* argv[]) {
    if (!initialize()) {
        std::cerr << "���� �ʱ�ȭ ����!" << std::endl;
        return -1;
    }

    // ���� ����
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

// ���� ����
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
bool isRunning = true;

// ���� �ʱ�ȭ �Լ�
bool initialize() {
    // SDL �� ����ý��� �ʱ�ȭ
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL �ʱ�ȭ ����: " << SDL_GetError() << std::endl;
        return false;
    }

    // ������ ����
    window = SDL_CreateWindow("Hood Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "������ ���� ����: " << SDL_GetError() << std::endl;
        return false;
    }

    // ������ ����
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "������ ���� ����: " << SDL_GetError() << std::endl;
        return false;
    }

    // SDL_Image �ʱ�ȭ
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_Image �ʱ�ȭ ����: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

// ���� ���� ������Ʈ
void update() {
    // ���� ���� ������Ʈ ���� �߰�
}

// ���� ȭ�� ������
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // ���� UI �� ���� ��� ������
    // ...

    SDL_RenderPresent(renderer);
}

// �̺�Ʈ ó��
void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // �߰� �̺�Ʈ ����
        // ...
    }
}

// �ڿ� ����
void cleanup() {
    // SDL ���� �ڿ� ����
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}

// ���� �Լ�
int main(int argc, char* argv[]) {
    if (!initialize()) {
        std::cerr << "���� �ʱ�ȭ ����!" << std::endl;
        return -1;
    }

    // ���� ����
    while (isRunning) {
        handleEvents();
        update();
        render();
    }

    cleanup();
    return 0;
}
