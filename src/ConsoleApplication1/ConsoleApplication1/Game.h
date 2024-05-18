#ifndef GAME_H
#define GAME_H

#include <vector>
#include "SDL2/SDL.h"
#include "Path.h"
#include "ChiSam.h"
#include "Renderer.h"

class Game {
public:
    Game() : window(nullptr), renderer(nullptr) {}
    ~Game() { clean(); }

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void render();
    void clean();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // GAME_H
