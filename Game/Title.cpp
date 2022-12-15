#include "Title.hpp"

Title::Title(Vector2f p_pos, int p_type)
	:pos(p_pos), type(p_type)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 64;
	currentFrame.h = 64;

};

int Title::getType() {
	return type;
}

SDL_Rect Title::getCurrentFrame() {
	return currentFrame;
}