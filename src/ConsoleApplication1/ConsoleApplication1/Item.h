#ifndef ITEM_H
#define ITEM_H

#include "SDL2/SDL.h"
#include <string>

class Item {
public:
    Item(const std::string& type, int x, int y);
    ~Item();

    void render(SDL_Renderer* renderer);
    std::string getType() const;

private:
    std::string type;
    SDL_Texture* texture;
    SDL_Rect position;

    void loadTexture(SDL_Renderer* renderer);
};

#endif // ITEM_H