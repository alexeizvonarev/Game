#pragma once
#include "LoadLvl.hpp"
#include "Title.hpp"
#include "Entity.hpp"
#include "Math.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>

class LoadLvl{
public:
	LoadLvl(const char* p_filePath, SDL_Texture* map_textures[], const int p_tileSize);
	std::vector<Title> GetTitles();
	std::vector<Entity> GetEntities();

	void LoadTiles(const char* p_filePath, const int p_tileSize);
	void setEntityPos(int entity_id, Vector2f p_newPos);
	void setEntityDisplayPos(int entity_id, Vector2f p_newPos);
	void setTilePos(int tile_id, Vector2f p_newPos);

	Entity* getEntity(int entity_id) {
		return &entities[entity_id];
	}
	int getPlayerTile() { return tile_player; };
	int getXmax() { return max_x; };
	int getEntCount() { return entCount; };
private:
	std::vector<Title> titles;
	std::vector<Entity> entities;
	int titleCount, entCount;
	int max_x;
	int tile_player;
};
