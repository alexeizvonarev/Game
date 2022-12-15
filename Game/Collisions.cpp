#include "Collisions.hpp"
#include "Math.hpp"
#include <vector>
#include <math.h>

void Collisions::collisionY(Entity* player, LoadLvl p_titles, int title_type, int title_size, bool it_move) {
	int player_title;

	float distance = std::abs(player->getSpeed().y);
	std::vector<Title> titles = p_titles.GetTitles();

	Title needPlayer_title = titles[0];
	
	const Vector2f ne_ppos = player->getPos();
	Vector2f n_pos = ne_ppos;

	Vector2f force = player->getSpeed();
	bool ItCollided = false;
	int MaxCollisions = 0;
	struct collY {
		bool Up = false;
		bool Down = false;
	};
	collY Y;
	// check Y up 
	setPlayerTileId(Vector2f(ne_ppos.x, ne_ppos.y + title_size / 2 - distance), p_titles.getXmax(), title_size, player_title);
	needPlayer_title = titles[player_title - p_titles.getXmax()];

	if ( title_type == needPlayer_title.getType() and MaxCollisions != 1) { Y.Up = true; MaxCollisions++; } //force.y = 0; n_pos.y += 0.1;
	
	setPlayerTileId(Vector2f(ne_ppos.x + title_size / 2, ne_ppos.y + title_size / 2 - distance), p_titles.getXmax(), title_size, player_title);
	needPlayer_title = titles[player_title - p_titles.getXmax()];

	if (title_type == needPlayer_title.getType() and MaxCollisions != 1) { Y.Up = true; MaxCollisions++; } //force.y = 0; n_pos.y += 0.1

	setPlayerTileId(Vector2f(ne_ppos.x - title_size / 2, ne_ppos.y + title_size / 2 - distance), p_titles.getXmax(), title_size, player_title);
	needPlayer_title = titles[player_title - p_titles.getXmax()];

	if (title_type == needPlayer_title.getType() and MaxCollisions != 1) { Y.Up = true; MaxCollisions++; } //force.y = 0; n_pos.y += 0.1;
	MaxCollisions = 0;

	// chek Y down

	setPlayerTileId(Vector2f(ne_ppos.x, ne_ppos.y - title_size / 2 + distance), p_titles.getXmax(), title_size , player_title);
	needPlayer_title = titles[player_title + p_titles.getXmax()];

	if ( title_type == needPlayer_title.getType() and MaxCollisions != 1) {Y.Down = true; MaxCollisions++; } //force.y = 0; n_pos.y -= 0.1

	setPlayerTileId(Vector2f(ne_ppos.x - title_size / 2, ne_ppos.y - title_size / 2 + distance), p_titles.getXmax(), title_size, player_title);
	needPlayer_title = titles[player_title + p_titles.getXmax()];

	if ( title_type == needPlayer_title.getType() and MaxCollisions != 1) {Y.Down = true; MaxCollisions++; }

	setPlayerTileId(Vector2f(ne_ppos.x + title_size / 2, ne_ppos.y - title_size / 2 + distance), p_titles.getXmax(), title_size, player_title);
	needPlayer_title = titles[player_title + p_titles.getXmax()];

	if ( title_type == needPlayer_title.getType() and MaxCollisions != 1) { Y.Down = true; MaxCollisions++; }


	if (MaxCollisions != 0) { ItCollided = true; };

	if (Y.Down)
	{
		force.y = 0; n_pos.y -= 0.1;
		if (force.x > 0 and !it_move) { force.x /= 1.2; }
		if (force.x < 0 and !it_move) { force.x /= 1.2; }
	}
	if (Y.Up) { force.y = 0; n_pos.y += 0.1; }

	player->SetGround(ItCollided);
	player->setForce(force);
	player->setPos(n_pos);
}

void Collisions::collisionX(Entity* player, LoadLvl p_titles, int title_type, int title_size) {
	float distance = std::abs(player->getSpeed().x);
	int player_title;
	std::vector<Title> titles = p_titles.GetTitles();

	Title needPlayer_title = titles[0];

	const Vector2f ne_ppos = player->getPos();
	Vector2f n_pos = ne_ppos;

	Vector2f force = player->getSpeed();
	struct collX {
		bool Left = false;
		bool Right = false;
	};
	collX X;
	int MaxCollisions = 0;

	// check X left 
	setPlayerTileId(Vector2f(ne_ppos.x + title_size / 2 - distance, ne_ppos.y), p_titles.getXmax(), title_size, player_title);
	needPlayer_title = titles[player_title - 1];

	if ( title_type == needPlayer_title.getType() and MaxCollisions != 1) { X.Left = true; MaxCollisions++; } //force.x = 0; n_pos.x += 0.1;

	setPlayerTileId(Vector2f(ne_ppos.x + title_size / 2 - distance,ne_ppos.y + title_size/2), p_titles.getXmax(), title_size, player_title);
	needPlayer_title = titles[player_title - 1];

	if ( title_type == needPlayer_title.getType() and MaxCollisions != 1) { X.Left = true; MaxCollisions++; }

	setPlayerTileId(Vector2f(ne_ppos.x + title_size / 2 - distance, ne_ppos.y - title_size/2), p_titles.getXmax(), title_size, player_title);
	needPlayer_title = titles[player_title - 1];

	if ( title_type == needPlayer_title.getType() and MaxCollisions != 1) { X.Left = true; MaxCollisions++; }
	// chek X right

	MaxCollisions = 0;

	setPlayerTileId(Vector2f(ne_ppos.x - title_size / 2 + distance, ne_ppos.y), p_titles.getXmax(), title_size, player_title);
	needPlayer_title = titles[player_title + 1];

	if ( title_type == needPlayer_title.getType() and MaxCollisions != 1) { X.Right = true; MaxCollisions++; } //force.x = 0; n_pos.x -= 0.1;

	setPlayerTileId(Vector2f(ne_ppos.x - title_size / 2 + distance, ne_ppos.y + title_size / 2), p_titles.getXmax(), title_size, player_title);
	needPlayer_title = titles[player_title + 1];

	if ( title_type == needPlayer_title.getType() and MaxCollisions != 1) { X.Right = true; MaxCollisions++; }

	setPlayerTileId(Vector2f(ne_ppos.x - title_size / 2 + distance, ne_ppos.y - title_size / 2 + distance), p_titles.getXmax(), title_size, player_title);
	needPlayer_title = titles[player_title + 1];

	if ( title_type == needPlayer_title.getType() and MaxCollisions != 1) { X.Right = true; n_pos.x -= 0.1; MaxCollisions++; }

	if(X.Right){ force.x = 0; n_pos.x -= 0.1;}
	if (X.Left) { force.x = 0; n_pos.x += 0.1;}

	player->setForce(force);
	player->setPos(n_pos);
}

void Collisions::setPlayerTileId(Vector2f player, int levelXmax, int TILE_SIZE, int& player_title) {
	player_title = std::ceil(((player.x - (TILE_SIZE / 2)) / TILE_SIZE) + (levelXmax * std::ceil((player.y - TILE_SIZE / 2) / TILE_SIZE)));
}