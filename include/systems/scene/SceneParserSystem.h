//
// Created by pylinskyi.k on 13.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_SCENEPARSERSYSTEM_H
#define PELAGEIA_IMMERSIVE_SCENEPARSERSYSTEM_H

#include <map>
#include <string>
#include "entities/scene/GameMapEntity.h"
#include "utilities/CoreTypeStructs.h"
#include "pugixml.hpp"
#include "components/scene/TileMapLayerComponent.h"

class SceneParserSystem {
public:
    static SceneParserSystem& GetInstance() {
        if (!_instance) _instance = new SceneParserSystem();
        return *_instance;
    };

    inline GameMapEntity GetGameMap(std::string id) { return _gameMaps[id]; }
    bool LoadMaps();

protected:
    SceneParserSystem() { if (_instance) throw std::logic_error("SceneParserSystem Instance already exists"); };

    static SceneParserSystem* _instance;

    std::string _gameMapsDirectory = "./GameMaps";

    std::map<std::string, GameMapEntity> _gameMaps;
    TilesetData LoadTilest(pugi::xml_node tilesetNode);
    TileMapLayerComponent LoadTileMap();
};

#endif  // PELAGEIA_IMMERSIVE_SCENEPARSERSYSTEM_H
