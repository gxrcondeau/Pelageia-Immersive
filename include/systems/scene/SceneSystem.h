//
// Created by pylinskyi.k on 19.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_SCENESYSTEM_H
#define PELAGEIA_IMMERSIVE_SCENESYSTEM_H

#include <memory>
#include "utilities/CoreTypeStructs.h"
#include "pugixml.hpp"
#include "components/scene/BaseLayer.h"
#include "entities/scene/Scene.h"

class SceneSystem {
public:
    static SceneSystem& GetInstance();

    std::unique_ptr<Scene> LoadScene(const std::string& sceneFilePath);

    TilesetData LoadTileset(pugi::xml_node& tilesetNode);

    std::unique_ptr<BaseLayer> LoadLayer(pugi::xml_node& layerNode);

private:
    SceneSystem();

    static SceneSystem* _instance;

    std::string _directory = "GameMaps/";
};

#endif  // PELAGEIA_IMMERSIVE_SCENESYSTEM_H
