#pragma once
#include "LoadLvl.hpp"
class Collisions
{
public:
	void setPlayerTileId(Vector2f player, int levelXmax, int TILE_SIZE, int& player_title);
	void collisionY(Entity* player, LoadLvl p_titles, int title_type, int title_size, bool it_move);
	void collisionX(Entity* player, LoadLvl p_titles, int title_type, int title_size);
	void checkTypeAndSet(int xORy);
};

