//
// Created by pylinskyi.k on 14.12.2023.
//
#include <filesystem>
#include "systems/scene/SceneParserSystem.h"
#include "SDL.h"

SceneParserSystem* SceneParserSystem::_instance;

std::shared_ptr<TileMapLayerComponent> SceneParserSystem::GetTileMapLayer(std::string gameMapFile) {
    pugi::xml_document xml;
    pugi::xml_parse_result parse_result = xml.load_file((_gameMapsDirectory + gameMapFile).c_str());
    if (parse_result.status != 0) SDL_Log("Failed to load Game Map XML file: %s", gameMapFile.c_str());

    pugi::xml_node root = xml.child("map");
    if (!root) SDL_Log("map element not found in Tile Map XML.");

    pugi::xml_node tilesetNode = root.child("tileset");
    if (!tilesetNode) SDL_Log("tileset element not found in Tile Map XML.");

    std::vector<TilesetData> tilesets;
    while (tilesetNode) {
        tilesets.push_back(GetTilest(tilesetNode));
        tilesetNode = tilesetNode.next_sibling("tileset");
    }

    pugi::xml_node layerNode = root.child("layer");
    if (!tilesetNode) SDL_Log("layer element not found in Tile Map XML.");

    std::vector<LayerData> layers;
    while (layerNode) {
        layers.push_back(GetLayer(layerNode));
        layerNode = layerNode.next_sibling("tileset");
    }

    return std::make_shared<TileMapLayerComponent>(TileMapLayerComponent(tilesets, layers));
}

TilesetData SceneParserSystem::GetTilest(pugi::xml_node tilesetNode) {
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

LayerData SceneParserSystem::GetLayer(pugi::xml_node layerNode) {
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

    return layer;
}
