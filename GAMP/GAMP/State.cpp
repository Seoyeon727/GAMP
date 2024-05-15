#include "state.h"
#include <iostream>

void State::Init(SDL_Renderer* renderer) {
    SDL_Surface* health_surface = IMG_Load("../../Resources/stateSprite.png");
    health_texture = SDL_CreateTextureFromSurface(renderer, health_surface);
    SDL_FreeSurface(health_surface);

    health_source_rect[0] = { 0, 0, 100, 100 };
    health_source_rect[1] = { 100, 0, 100, 100 };

    health_destination_rect.x = 300;
    health_destination_rect.y = 200;
    health_destination_rect.w = health_source_rect[0].w;
    health_destination_rect.h = health_source_rect[0].h;
}

void State::Update(int health) {
    this->health = health;
    if (health >= 70) {
        health_image_mode = 0;
    }
    else {
        health_image_mode = 1;
    }
}

void State::Render(SDL_Renderer* renderer) {
    if (health_image_mode == 0) {
        health_source_rect[0].x = 0;
    }
    else if (health_image_mode == 1) {
        health_source_rect[0].x = 100;
    }

    SDL_RenderCopy(renderer, health_texture, &health_source_rect[0], &health_destination_rect);
}

void State::Clear() {
    SDL_DestroyTexture(health_texture);
}
