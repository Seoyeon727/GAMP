#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <string>
#include <vector>

// 스프라이트 클래스 정의
class Sprite {
public:
    Sprite(const std::string& imagePath, SDL_Renderer* renderer);
    ~Sprite();

    void draw(SDL_Renderer* renderer, int x, int y, int width, int height);
    bool isLoaded() const;

private:
    SDL_Texture* texture;
    bool loaded;
};

// 그래픽 엔진 클래스 정의
class Graphics {
public:
    Graphics(SDL_Renderer* renderer);
    ~Graphics();

    // 배경 및 인터페이스 그리기
    void drawBackground(const Sprite& background);
    void drawInterface();
    void drawPlayer(const Sprite& playerSprite, int x, int y);
    void drawEnemy(const Sprite& enemySprite, int x, int y);
    void drawText(const std::string& text, int x, int y);

private:
    SDL_Renderer* renderer;
    std::vector<Sprite> backgrounds;
    std::vector<Sprite> interfaceElements;
};

#endif
