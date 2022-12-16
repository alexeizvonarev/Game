#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, Vector2f p_dispos, Vector2f p_force, SDL_Texture* p_tex, bool isBlock, Vector2f p_size, double p_angle, Vector2f p_center, SDL_RendererFlip displayM, SDL_Rect p_slice)
	:pos(p_pos), tex(p_tex), speed(p_force), display_pos(p_dispos), slice(p_slice)
{
	angle = p_angle;
	display_mode = displayM;

	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_size.x;
	currentFrame.h = p_size.y;
	
	center.x = p_center.x;
	center.y = p_center.y;
	if (p_center.x == -1) { center.x = p_size.x / 2; }
	else { center.x = p_center.x; }

	if (p_center.y == -1) { center.y = p_size.y / 2; }
	else { center.y = p_center.y; }

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
SDL_Rect Entity::getSlice() {
	return slice;
}
