#pragma once
#include <SDL.h>
#include <SDL_image.h>

class ElementHUD;
#include "Entity.hpp"
class RenderWindow
{
public:
	SDL_Renderer* renderer;

	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	SDL_Window* getWindow() { return window; };

	int getRefreshRate();

	void clear();
	void cleanUp();

	SDL_Renderer& getRender();

	void renderHUD(ElementHUD &p_entity);
	void render(Entity& p_entity);

	void display();
private:
	SDL_Window* window;
};