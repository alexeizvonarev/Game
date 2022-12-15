#pragma once
#include "Math.hpp"
#include "RenderWindow.hpp"
#include "Math.hpp"

class ElementHUD {
public:

	ElementHUD(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_from);

	SDL_Rect getCurrentFrame() { return currentFrame; };
	Vector2f getDisplayPos() { return pos; };
	SDL_Texture* getTex() { return tex; };

	void setPos(Vector2f p_pos) { pos = p_pos; };

private:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};

class Mouse {
public:
	Vector2f mouse_pos;
	Mouse(const char* path, SDL_Renderer &ren) {
		tex = IMG_LoadTexture(&ren,path);
		rect.w = 32;
		rect.h = 32;
		point.w = 1;
		point.h = 1;
		SDL_ShowCursor(false);
	}

	void update() {
		SDL_GetMouseState(&rect.x, &rect.y);
		point.x = rect.x;
		point.y = rect.y;
		rect.x -= 16;
		rect.y -= 16;
		mouse_pos = Vector2f(point.x, point.y);
	}

	void draw(SDL_Renderer &ren) {
		SDL_RenderCopy(&ren, tex, NULL, &rect);
	}
private:
	SDL_Texture* tex;
	SDL_Rect rect;
	SDL_Rect point;
};