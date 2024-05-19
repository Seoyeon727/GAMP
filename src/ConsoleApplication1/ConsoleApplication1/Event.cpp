#include "Event.h"
#include "SDL2/SDL_image.h"

Event::Event(const std::string& description) : description(description), texture(nullptr), position({0, 0, 800, 600}) {}

Event::~Event() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Event::trigger() {
    //todo: Add logic to handle event
}

void Event::render(SDL_Renderer* renderer) {
    if (!texture) {
        loadTexture(renderer);
    }
    SDL_RenderCopy(renderer, texture, nullptr, &position);
}

void Event::loadTexture(SDL_Renderer* renderer) {
    std::string filepath = "../img/events/" + description + ".png";
    SDL_Surface* surface = IMG_Load(filepath.c_str());
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}