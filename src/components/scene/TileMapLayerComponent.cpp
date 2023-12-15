//
// Created by pylinskyi.k on 14.12.2023.
//

#include "SDL.h"
#include "components/scene/TileMapLayerComponent.h"
#include "systems/graphics/TextureManagerSystem.h"

TextureManagerSystem* TextureManagerSystem::_instance = nullptr;

TileMapLayerComponent::TileMapLayerComponent(std::vector<TilesetData> tilesets, std::vector<std::vector<int>> tilemap) {
    _tileSize = tilesets.size() > 0 ? tilesets[0].TileSize : 0;
    _rowCount = tilemap.size();
    _colCount = _rowCount > 0 ? tilemap[0].size() : 0;
    _tilemap = tilemap;

    for (const auto& tileset : tilesets) {
        bool success = TextureManagerSystem::GetInstance().LoadTexture(tileset.Name, "GameMaps/" + tileset.Source);
        if (!success) {
            SDL_Log("Failed to load tileset texture %s from source %s", tileset.Name, tileset.Source);
        }
    }
}
