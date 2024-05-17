#ifndef RENDERER_H
#define RENDERER_H

#include "SDL2/SDL.h"
#include "ChiSam.h"
#include "Path.h"

class Renderer {
public:
    Renderer(SDL_Renderer* renderer);
    ~Renderer();

    void render(ChiSam* chihsami, Path* path);

private:
    SDL_Renderer* renderer;
};

#endif // RENDERER_H