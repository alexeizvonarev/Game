#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Math.hpp"

class Entity
{
public:
	SDL_RendererFlip display_mode;
	int Health;
	double angle;
	SDL_Point center;


	Entity(Vector2f p_pos,
		Vector2f p_dispos,
		Vector2f p_force,
		SDL_Texture* p_tex,
		bool isBlock = true,
		Vector2f size = Vector2f(64, 64),
		double angle = 0,
		Vector2f p_center = Vector2f(-1, -1),
		SDL_RendererFlip displayM = SDL_FLIP_NONE,
		SDL_Rect p_slice = SDL_Rect{0,0,64,64} );

	Vector2f& getPos() {
		return pos; 
	}
	Vector2f& getDisplayPos() {
		return display_pos;
	}

	Vector2f& getSpeed() {
		return speed;
	}
	bool ItGround() {return p_OnGround;};
	void SetGround(bool ground) { p_OnGround = ground; };

	void setPos(Vector2f n_pos) {
		pos = n_pos;
	}
	void setDisplayPos(Vector2f n_pos) {
		display_pos = n_pos;
	}
	void setSize(Vector2f n_size) {
		currentFrame.h = n_size.y;
		currentFrame.w = n_size.x;
	}
	
	void setForce(Vector2f n_force){
		speed = n_force;
	}
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	SDL_Rect getSlice();
private:
	bool p_OnGround;
	Vector2f pos;
	Vector2f display_pos;

	Vector2f speed;
	SDL_Rect currentFrame;
	SDL_Rect slice;
	SDL_Texture* tex;
};

