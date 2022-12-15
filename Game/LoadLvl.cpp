#include "LoadLvl.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Title.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>

LoadLvl::LoadLvl(const char* p_filePath, SDL_Texture* map_textures[], const int p_tileSize)
{
    std::vector<std::string> result;
    {
        //читаем файл...
        std::string line;

        std::ifstream in(p_filePath);
        if (in.is_open())
        {
            while (getline(in, line))
            {
                std::string cur_num;
                for (int i = 0; i < line.length(); i++) {
                    const char symbol = line[i];
                    if (symbol == '.') {
                        result.push_back(cur_num);
                        cur_num = "";
                    }
                    else {
                        cur_num.push_back(symbol);
                    }
                }
                result.push_back("y");
            }
        }
        in.close();
    }
    //теперь создаём entities!

    int i = 0;
    float x = 0;
    float y = 0;
    for (; i <= result.size()-1; i++)
    {
        std::string element = result[i];
        int TileId = atoi(element.c_str());
        if (element == "y") {
            y += p_tileSize;
            x = 0;
        }
        else {
            entities.push_back(Entity(Vector2f(x, y), Vector2f(x, y),Vector2f(0,0),map_textures[TileId]));
            x += p_tileSize;
        }
    }
    entCount = i;
};
void LoadLvl::LoadTiles(const char* p_filePath, const int p_tileSize) {
    std::vector<std::string> result;
    {

        //читаем файл...
        std::string line;

        std::ifstream in(p_filePath);
        if (in.is_open())
        {
            while (getline(in, line))
            {
                std::string cur_num;
                for (int i = 0; i < line.length(); i++) {
                    const char symbol = line[i];
                    if (symbol == '.') {
                        result.push_back(cur_num);
                        cur_num = "";
                    }
                    else {
                        cur_num.push_back(symbol);
                    }
                }
                result.push_back("y");
            }
        }
        in.close();
    }
    //теперь создаём titles!

    int i = 0;
    float x = 0;
    float y = 0;
    for (; i <= result.size() - 1; i++)
    {
        std::string element = result[i];
        int TileId = atoi(element.c_str());
        if (element == "y") {
            if (x / p_tileSize > max_x) { max_x = x / p_tileSize; }
            y += p_tileSize;
            x = 0;
        }
        else {
            if (TileId == 2) {
                tile_player = i-(y/p_tileSize);
            }
            titles.push_back(Title(Vector2f(x, y), TileId));
            x += p_tileSize;
        }
    }
    titleCount = i;
}
void LoadLvl::setTilePos(int tile_id, Vector2f p_newPos) {
    titles[tile_id].setPos(p_newPos);
}
void LoadLvl::setEntityPos(int entity_id, Vector2f p_newPos) {
    entities[entity_id].setPos(p_newPos);
}
void LoadLvl::setEntityDisplayPos(int entity_id, Vector2f p_newPos) {
    entities[entity_id].setDisplayPos(p_newPos);
}

std::vector<Title> LoadLvl::GetTitles(){
    if (titles.size() != 0) {
        return titles;
    }
}
std::vector<Entity> LoadLvl::GetEntities() {
    if (entities.size() != 0) {
        return entities;
    }
}