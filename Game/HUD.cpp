#include <SDL.h>
#include "HUD.hpp"

ElementHUD::ElementHUD(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_from)
	:pos(p_pos), tex(p_tex)
{
	currentFrame.x = p_from.x;
	currentFrame.y = p_from.y;
	currentFrame.w = 64;
	currentFrame.h = 64;
}
