#include "ChiSam.h"
#include "SDL2/SDL_image.h"

ChiSam::ChiSam() : texture(nullptr), position({ 100, 100, 50, 50 }), stats() {}

ChiSam::~ChiSam() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void ChiSam::moveLeft() {
    position.x -= 10;
}

void ChiSam::moveRight() {
    position.x += 10;
}

void ChiSam::moveUp() {
    position.y -= 10;
}

void ChiSam::moveDown() {
    position.y += 10;
}

void ChiSam::collectItem(const std::string& itemType) {
    if (itemType == "churu") {
        stats.increaseHealth(10);
    }
    else if (itemType == "ribbon") {
        stats.increasePopularity(5);
    }
    //todo: Add logic for other item types
}

void ChiSam::render(SDL_Renderer* renderer) {
    if (!texture) {
        loadTexture(renderer);
    }
    SDL_RenderCopy(renderer, texture, nullptr, &position);
}

int ChiSam::getHealth() const {
    return stats.getHealth();
}

int ChiSam::getStress() const {
    return stats.getStress();
}

int ChiSam::getPopularity() const {
    return stats.getPopularity();
}

int ChiSam::getAcademicPerformance() const {
    return stats.getAcademicPerformance();
}

void ChiSam::loadTexture(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("../img/chihsami.png");
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}
