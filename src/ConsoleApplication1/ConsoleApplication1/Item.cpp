#include "Item.h"
#include "SDL2/SDL_image.h"

Item::Item(const std::string& type, int x, int y) : type(type), texture(nullptr), position({x, y, 32, 32}) {}

Item::~Item() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Item::render(SDL_Renderer* renderer) {
    if (!texture) {
        loadTexture(renderer);
    }
    SDL_RenderCopy(renderer, texture, nullptr, &position);
}

std::string Item::getType() const {
    return type;
}

void Item::loadTexture(SDL_Renderer* renderer) {
    std::string filepath = "../img/items/" + type + ".png";
    SDL_Surface* surface = IMG_Load(filepath.c_str());
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}