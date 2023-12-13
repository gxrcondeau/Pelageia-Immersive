//
// Created by pylinskyi.k on 07.11.2023.
//

#ifndef PELAGEIA_IMMERSIVE_TILEMAPPARSER_H
#define PELAGEIA_IMMERSIVE_TILEMAPPARSER_H

#include <string>
#include <map>
#include "TileLayer.h"
#include "GameMap.h"
#include "pugixml.hpp"

class TileMapParser
{
public:
    bool Load();
    bool Clean();

    inline GameMap* GetMap(std::string id) { return m_MapDict[id]; };
    inline static TileMapParser* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new TileMapParser()); }

private:
    TileMapParser(){};
    static TileMapParser* s_Instance;
    std::map<std::string, GameMap*> m_MapDict;

    bool Parse(std::string id, std::string source);
    Tileset ParseTileset(pugi::xml_node* xmlTileset);
    TileLayer* ParseTileLayer(pugi::xml_node* xmlTileLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);
};

#endif  // PELAGEIA_IMMERSIVE_TILEMAPPARSER_H
