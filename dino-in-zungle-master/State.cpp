#include "State.h"

State::State()
{
	position.x = 0;
	position.y = 0;

	currentSprite = STATE_BAD;
}

State::State(int x, int y)
{
	position.x = x;
	position.y = y;

	currentSprite = STATE_BAD;
}

void State::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

void State::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gStateTexture)
{
	gStateTexture.Render(position.x, position.y, gRenderer, currentClip);
}