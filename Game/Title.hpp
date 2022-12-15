#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Math.hpp"

class Title
{
public:
	Title(Vector2f p_pos, int p_type);
	int getType();
	Vector2f& getPos() {
		return pos;
	}
	void setPos(Vector2f n_pos) {
		pos = n_pos;
	}
	SDL_Rect getCurrentFrame();
private:
	int type;
	Vector2f pos;
	SDL_Rect currentFrame;
};

