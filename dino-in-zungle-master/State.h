#ifndef STATE_H_
#define STATE_H_

#include "Game_Base.h"
#include "LTexture.h"

class State
{
public:
	StateSprite currentSprite;

	State();

	State(int x, int y);

	void SetPosition(int x, int y);

	void Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture);

private:
	SDL_Point position;
};

#endif // !STATE_H_