#include "Graphics.h"
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_image.h>

// Sprite 생성자
Sprite::Sprite(const std::string& imagePath, SDL_Renderer* renderer) {
    // 이미지 파일을 로드하여 SDL 텍스처로 변환
    SDL_Surface* tempSurface = IMG_Load(imagePath.c_str());
    if (!tempSurface) {
        std::cerr << "이미지 로드 실패: " << IMG_GetError() << std::endl;
        loaded = false;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!texture) {
        std::cerr << "텍스처 생성 실패: " << SDL_GetError() << std::endl;
        loaded = false;
    }
    else {
        loaded = true;
    }
}

// Sprite 소멸자
Sprite::~Sprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

// 텍스처를 화면에 그리기
void Sprite::draw(SDL_Renderer* renderer, int x, int y, int width, int height) const { // const 한정자 추가
    if (!loaded) return;

    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

// 텍스처 로드 여부 확인
bool Sprite::isLoaded() const {
    return loaded;
}

// Graphics 생성자
Graphics::Graphics(SDL_Renderer* renderer) : renderer(renderer) {
    // TTF 초기화
    if (TTF_Init() == -1) {
        std::cerr << "TTF 초기화 실패: " << TTF_GetError() << std::endl;
    }

    // 기타 필요한 배경 및 인터페이스 요소를 로드할 수 있습니다.
}

// Graphics 소멸자
Graphics::~Graphics() {
    // 리소스 정리
    TTF_Quit();
}

// 배경 그리기
void Graphics::drawBackground(const Sprite& background) {
    background.draw(renderer, 0, 0, 800, 600); // 전체 화면에 배경 그리기
}

// 인터페이스 그리기
void Graphics::drawInterface() {
    // 인터페이스 요소를 화면에 그리기
}

// 플레이어 그리기
void Graphics::drawPlayer(const Sprite& playerSprite, int x, int y, int width, int height) {
    playerSprite.draw(renderer, x, y, width, height); // 플레이어 스프라이트 그리기
}

// 적 그리기
void Graphics::drawEnemy(const Sprite& enemySprite, int x, int y, int width, int height) {
    enemySprite.draw(renderer, x, y, width, height); // 적 스프라이트 그리기
}

// 텍스트 그리기
void Graphics::drawText(const std::string& text, int x, int y) {
    // 텍스트를 그리기 위한 SDL_ttf 로직
    TTF_Font* font = TTF_OpenFont("path/to/font.ttf", 24);
    if (!font) {
        std::cerr << "폰트 로드 실패: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = { 255, 255, 255 }; // 흰색 텍스트
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "텍스트 렌더링 실패: " << TTF_GetError() << std::endl;
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
