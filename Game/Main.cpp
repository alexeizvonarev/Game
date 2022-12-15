#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <cmath> 

#include "Collisions.hpp"
#include "HUD.hpp"
#include "Utils.hpp"
#include "Entity.hpp"
#include "RenderWindow.hpp"
#include "LoadLvl.hpp"

void keyboard(bool& game_state, bool* KEYS, Vector2f& Cursor) {
	// message processing loop
	SDL_Event event;
	int x;
	int y;

	SDL_GetMouseState(&x, &y);
	Cursor = Vector2f(x, y);

	while (SDL_PollEvent(&event)) {
		// check for messages
		switch (event.type) {
			// exit if the window is closed
		case SDL_QUIT:
			game_state = 0; // set game state to done,(do what you want here)
			break;
			// check for keypresses
		case SDL_KEYDOWN:
			if (event.key.keysym.sym > 322) { break; }
			KEYS[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym > 322) { break; }
			KEYS[event.key.keysym.sym] = false;
			break;
		default:
			break;
		}
	} // end of message processing
}

int main(int argv, char* args[])
{
	if (SDL_INIT_EVERYTHING < 0) {
		std::cout << "Error!" << std::endl;
	}
	else {
		std::cout << "Sucessfuly!" << std::endl;
	}
	const int DEFAULT_WIDTH = 1280;
	const int DEFAULT_HEIGHT = 720;
	int TILE_SIZE = 64;
	const float MAX_SPEED = 3;
	const float FORCE = 1;
	const float JUMP_POWER = 8;

	const float HALF_HEIGHT = DEFAULT_HEIGHT / 2;
	const float HALF_WIDTH = DEFAULT_WIDTH / 2;

	RenderWindow window("Game v1.0", DEFAULT_WIDTH, DEFAULT_HEIGHT);

	std::cout << window.getRefreshRate() << std::endl;

	const char *to_load[] =
	{
		"Data/Textures/Tiles/free.png",
		"Data/Textures/Tiles/grass.png",
		"Data/Textures/Tiles/sky.png",

		"Data/Textures/Player/player.png",
	};
	const int len_load = sizeof(to_load) / sizeof(*to_load);

	SDL_Texture* map_textures[len_load] = {};

	for (int i = 0; i <= len_load-1; i++) {
		SDL_Texture* curTex = window.loadTexture(to_load[i]);
		map_textures[i] = curTex;
	}

	std::cout << "Textures loaded...\n";
	std::cout << "Starting creating lvl\n";

	LoadLvl level("Data/Maps/test.ATSmap",map_textures, TILE_SIZE);
	level.LoadTiles("Data/Maps/test.TTSmap", TILE_SIZE);

	int player_title = level.getPlayerTile();
	Vector2f Centre(HALF_WIDTH - TILE_SIZE / 2, HALF_HEIGHT - TILE_SIZE / 2);

	//player create

	Entity player(level.GetTitles()[player_title].getPos(), Centre, Vector2f(0, 0), map_textures[3], false);

	SDL_Texture* curTex = window.loadTexture("Data/Textures/Player/railgun.png");
	Entity gun(player.getPos(), Centre, Vector2f(0, 0), curTex, true, Vector2f(128, 64), 0, Vector2f(32,-1));

	Mouse mouse("Data/Textures/Player/aim.png",*window.renderer);

	std::cout << "Level was created!\n";

	bool gameRunning = true;
	SDL_Event event;
	Collisions collisions;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();
	float refreshRateFPS = window.getRefreshRate() / 1000;
	bool KEYS[322];  // 322 is the number of SDLK_DOWN events
	for (int i = 0; i < 322; i++) { // init them all to false
		KEYS[i] = false;
	}

	Vector2f Cursor(0, 0);

	while (gameRunning)
	{
		mouse.update();

		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;
		accumulator += frameTime;
		while (accumulator >= timeStep)
		{
			collisions.collisionX(&player, level, 1, TILE_SIZE);
			collisions.collisionY(&player, level, 1, TILE_SIZE, KEYS[SDLK_a] or KEYS[SDLK_d]);

			Vector2f f = player.getSpeed();
			Vector2f p = player.getPos();

			float x = f.x;
			float y = f.y;
			y += 0.03;
			bool onGround = player.ItGround();

			if (KEYS[SDLK_w]) {
				if (onGround) {
					std::cout << "Try to jump*\n";
					y = -JUMP_POWER/2;
					p.y -= JUMP_POWER/2;

					player.SetGround(false);
				}
			}

			if (KEYS[SDLK_PLUS]) {
				TILE_SIZE += 12;
			}

			if (KEYS[SDLK_a]) {
				if (f.x > -MAX_SPEED)
					if (onGround) { x -= FORCE; }
					else { x -= FORCE / 8; }
			}
			if (KEYS[SDLK_d]) {
				if (f.x < MAX_SPEED)
					if (onGround) { x += FORCE; }
					else { x += FORCE / 8; }
			}

			Vector2f new_pos(x, y);
			player.setForce(new_pos);

			keyboard(gameRunning, KEYS, Cursor);
			accumulator -= timeStep;

			new_pos = Vector2f(p.x + f.x, p.y + f.y);
			player.setPos(new_pos);

			Vector2f pd = player.getDisplayPos();

			for (int id = 0; id <= level.getEntCount(); id++) {
				Vector2f e_p = level.getEntity(id).getPos();
				level.setEntityDisplayPos(id, Vector2f(pd.x+e_p.x-p.x, pd.y +e_p.y-p.y));
			}
			//player.setDisplayPos(Vector2f(p.x + f.x, p.y + f.y));
			float angle = utils::getAngleFromVector(mouse.mouse_pos.x, mouse.mouse_pos.y);
			gun.angle = angle;
			if (angle > 90 and angle < 270) { gun.display_mode = SDL_FLIP_VERTICAL; }
			else{ gun.display_mode = SDL_FLIP_NONE; }
			std::cout << angle << '\n';
		}

		const float alpha = accumulator / timeStep;

		//render
		window.clear();
		
		for (Entity& e : level.GetEntities()) {
			window.render(e);
		}
		window.render(gun);
		window.render(player);

		mouse.draw(*window.renderer);

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;
		if (frameTicks < refreshRateFPS) {
			SDL_Delay(refreshRateFPS - frameTicks);
		}
	}

	window.cleanUp();
	SDL_Quit();
	return 0;
}