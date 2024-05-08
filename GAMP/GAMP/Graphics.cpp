#include "Graphics.h"
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_image.h>

// Sprite ������
Sprite::Sprite(const std::string& imagePath, SDL_Renderer* renderer) {
    // �̹��� ������ �ε��Ͽ� SDL �ؽ�ó�� ��ȯ
    SDL_Surface* tempSurface = IMG_Load(imagePath.c_str());
    if (!tempSurface) {
        std::cerr << "�̹��� �ε� ����: " << IMG_GetError() << std::endl;
        loaded = false;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!texture) {
        std::cerr << "�ؽ�ó ���� ����: " << SDL_GetError() << std::endl;
        loaded = false;
    }
    else {
        loaded = true;
    }
}

// Sprite �Ҹ���
Sprite::~Sprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

// �ؽ�ó�� ȭ�鿡 �׸���
void Sprite::draw(SDL_Renderer* renderer, int x, int y, int width, int height) const { // const ������ �߰�
    if (!loaded) return;

    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

// �ؽ�ó �ε� ���� Ȯ��
bool Sprite::isLoaded() const {
    return loaded;
}

// Graphics ������
Graphics::Graphics(SDL_Renderer* renderer) : renderer(renderer) {
    // TTF �ʱ�ȭ
    if (TTF_Init() == -1) {
        std::cerr << "TTF �ʱ�ȭ ����: " << TTF_GetError() << std::endl;
    }

    // ��Ÿ �ʿ��� ��� �� �������̽� ��Ҹ� �ε��� �� �ֽ��ϴ�.
}

// Graphics �Ҹ���
Graphics::~Graphics() {
    // ���ҽ� ����
    TTF_Quit();
}

// ��� �׸���
void Graphics::drawBackground(const Sprite& background) {
    background.draw(renderer, 0, 0, 800, 600); // ��ü ȭ�鿡 ��� �׸���
}

// �������̽� �׸���
void Graphics::drawInterface() {
    // �������̽� ��Ҹ� ȭ�鿡 �׸���
}

// �÷��̾� �׸���
void Graphics::drawPlayer(const Sprite& playerSprite, int x, int y, int width, int height) {
    playerSprite.draw(renderer, x, y, width, height); // �÷��̾� ��������Ʈ �׸���
}

// �� �׸���
void Graphics::drawEnemy(const Sprite& enemySprite, int x, int y, int width, int height) {
    enemySprite.draw(renderer, x, y, width, height); // �� ��������Ʈ �׸���
}

// �ؽ�Ʈ �׸���
void Graphics::drawText(const std::string& text, int x, int y) {
    // �ؽ�Ʈ�� �׸��� ���� SDL_ttf ����
    TTF_Font* font = TTF_OpenFont("path/to/font.ttf", 24);
    if (!font) {
        std::cerr << "��Ʈ �ε� ����: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = { 255, 255, 255 }; // ��� �ؽ�Ʈ
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "�ؽ�Ʈ ������ ����: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}
