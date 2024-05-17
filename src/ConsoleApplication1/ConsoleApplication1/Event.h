#ifndef EVENT_H
#define EVENT_H

#include "SDL2/SDL.h"
#include <string>

class Event {
public:
    Event(const std::string& description);
    ~Event();

    void trigger();
    void render(SDL_Renderer* renderer);

private:
    std::string description;
    SDL_Texture* texture;
    SDL_Rect position;

    void loadTexture(SDL_Renderer* renderer);
};

#endif // EVENT_H