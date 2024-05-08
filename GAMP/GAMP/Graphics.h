#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <string>
#include <vector>

// ��������Ʈ Ŭ���� ����
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

// �׷��� ���� Ŭ���� ����
class Graphics {
public:
    Graphics(SDL_Renderer* renderer);
    ~Graphics();

    // ��� �� �������̽� �׸���
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
