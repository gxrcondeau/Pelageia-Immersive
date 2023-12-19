//
// Created by pylinskyi.k on 19.12.2023.
//
#include "SDL.h"
#include "systems/scene/SceneSystem.h"
#include "systems/scene/LayerFactory.h"

SceneSystem::SceneSystem() {}

SceneSystem& SceneSystem::GetInstance() {
    if (!_instance) {
        _instance = new SceneSystem();
    }
    return *_instance;
}

std::unique_ptr<Scene> SceneSystem::LoadScene(const std::string& sceneFilePath) {
    pugi::xml_document xml;
    std::string filePath = _directory + sceneFilePath;
    pugi::xml_parse_result parse_result = xml.load_file(filePath.c_str());
    if (parse_result.status != 0) SDL_Log("Failed to load Game Map XML file: %s", filePath.c_str());

    pugi::xml_node mapNode = xml.child("map");
    if (!mapNode) SDL_Log("map element not found in Tile Map XML.");

    int mapWidth = mapNode.attribute("width").as_int();
    int mapHeight = mapNode.attribute("height").as_int();
    int mapTileSize = mapNode.attribute("tilewidth").as_int();

    pugi::xml_node tilesetNode = mapNode.child("tileset");
    if (!tilesetNode) SDL_Log("tileset element not found in Tile Map XML.");

    std::vector<TilesetData> tilesets;
    while (tilesetNode) {
        tilesets.push_back(LoadTileset(tilesetNode));
        tilesetNode = tilesetNode.next_sibling("tileset");
    }

    pugi::xml_node layerNode = mapNode.child("layer");
    if (!layerNode) SDL_Log("layer element not found in Tile Map XML.");

    std::vector<std::unique_ptr<BaseLayer>> layers;
    while (layerNode) {
        layers.push_back(LoadLayer(layerNode));
        layerNode = layerNode.next_sibling("layer");
    }

    return std::make_unique<Scene>(mapWidth, mapHeight, mapTileSize, tilesets, std::move(layers));
}


TilesetData SceneSystem::LoadTileset(pugi::xml_node& tilesetNode) {
    TilesetData tileset;
    tileset.Name = tilesetNode.attribute("name").as_string();

    tileset.FirstID = tilesetNode.attribute("firstgid").as_int();
    tileset.LastID = tileset.FirstID + tileset.TileCount - 1;

    tileset.ColCount = tilesetNode.attribute("columns").as_int();
    tileset.RowCount = tileset.TileCount / tileset.ColCount;

    tileset.TileCount = tilesetNode.attribute("tilecount").as_int();
    tileset.TileSize = tilesetNode.attribute("tilewidth").as_int();

    const auto image = tilesetNode.child("image");
    tileset.Source = image.attribute("source").as_string();

    const auto tile = tilesetNode.child("tile");
    const auto anim = tile.child("animation");
    auto frame = anim.child("frame");

    while (frame) {
        int tilegid = tileset.FirstID + frame.attribute("tileid").as_int();
        tileset.AnimationFrames.push_back(tilegid);
        frame = frame.next_sibling("frame");
    }

    return tileset;
}

std::unique_ptr<BaseLayer> SceneSystem::LoadLayer(pugi::xml_node& layerNode) {
    LayerData layer;

    layer.Width = layerNode.attribute("width").as_int();
    layer.Height = layerNode.attribute("height").as_int();
    layer.Map.resize(layer.Width, std::vector<int>(layer.Height, 0));

    pugi::xml_node dataNode = layerNode.child("data");
    if (dataNode) {
        std::string encoding = dataNode.attribute("encoding").value();

        std::string csvData = dataNode.text().get();
        std::istringstream readStream(csvData);
        std::string cell;

        for (int row = 0; row < layer.Width; row++) {
            for (int col = 0; col < layer.Height; col++) {
                std::getline(readStream, cell, ',');
                std::stringstream writeStream(cell);
                writeStream >> layer.Map[row][col];

                if (!readStream.good()) break;
            }
        }
    }

    return LayerFactory::CreateLayer(layer);
}
