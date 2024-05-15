#ifndef STATE_H
#define STATE_H

#include <SDL.h>
#include <SDL_image.h>

class State {
public:
    void Init(SDL_Renderer* renderer);
    void Update(int health);
    void Render(SDL_Renderer* renderer);
    void Clear();

private:
    int health;
    int health_image_mode;
    SDL_Texture* health_texture;
    SDL_Rect health_source_rect[2];
    SDL_Rect health_destination_rect;
};

#endif
