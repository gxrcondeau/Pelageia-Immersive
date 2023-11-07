//
// Created by pylinskyi.k on 07.11.2023.
//

#ifndef PELAGEIA_IMMERSIVE_MAPPARSER_H
#define PELAGEIA_IMMERSIVE_MAPPARSER_H


#include <string>
#include "TileLayer.h"
#include "tinyxml.h"
#include "GameMap.h"

class MapParser {
public:
    bool Load();
    bool Clean();

    inline GameMap* GameMaps();
    inline static MapParser* GetInstance() { return s_Instance = ( s_Instance != nullptr ? s_Instance : new MapParser()); }

private:
    MapParser() {};
    static MapParser* s_Instance;

    bool Parse(std::string id, std::string source);
    Tileset ParseTileset(TiXmlElement* xmlTileset);
    TileLayer* ParseTileLayer(TiXmlElement* xmlTileLayer);
};


#endif //PELAGEIA_IMMERSIVE_MAPPARSER_H
