#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, Vector2f p_dispos, Vector2f p_force , SDL_Texture* p_tex, bool isBlock)
	:pos(p_pos), tex(p_tex), speed(p_force), display_pos(p_dispos)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 64;
	currentFrame.h = 64;

	p_OnGround = false;
	if (isBlock) {Health = -1;}
	else {Health = 100;}
}

SDL_Texture* Entity::getTex() {
	return tex;
}
SDL_Rect Entity::getCurrentFrame() {
	return currentFrame;
}
