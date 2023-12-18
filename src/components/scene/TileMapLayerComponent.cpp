//
// Created by pylinskyi.k on 14.12.2023.
//

#include "SDL.h"
#include "components/scene/TileMapLayerComponent.h"
#include "systems/graphics/TextureManagerSystem.h"
#include "mathematics/IsometricConvertor.h"

TileMapLayerComponent::TileMapLayerComponent(std::vector<TilesetData> tilesets, std::vector<LayerData> layers) {
    _tileSize = tilesets.size() > 0 ? tilesets[0].TileSize : 0;
    _rowCount = layers.size() > 0 ? layers[0].Width : 0;
    _colCount = layers.size() > 0 ? layers[0].Height : 0;

    _tilesets = tilesets;
    _layers = layers;

    for (const auto tileset : tilesets) {
        bool success = TextureManagerSystem::GetInstance().LoadTexture(tileset.Name, "GameMaps/" + tileset.Source);
        if (!success) {
            SDL_Log("Failed to load tileset texture %s from source %s", tileset.Name.c_str(), tileset.Source.c_str());
        }
    }
}

void TileMapLayerComponent::Render() {
    for (unsigned row = 0; row < _rowCount; row++)
    {
        for (unsigned col = 0; col < _colCount; col++)
        {
            for (const auto layer : _layers){
                int tileID = layer.Map[row][col];

                if (tileID > 0)
                {
                    for (auto tileset : _tilesets)
                    {
                        std::string tilesetName = tileset.Name;
                        int tileSize = tileset.TileSize;

                        int x = IsometricConvertor::GetIsoX(row, col, tileSize);
                        int y = IsometricConvertor::GetIsoY(row, col, tileSize);

                        if (tileset.AnimationFrames.size() > 0 && tileID == tileset.AnimationFrames[0])
                        {
                            int frame = (SDL_GetTicks() / 100) % tileset.AnimationFrames.size();

                            int tileRow = (tileset.AnimationFrames[frame] - tileset.FirstID + 1) / tileset.ColCount;
                            int tileCol = (tileset.AnimationFrames[frame] - tileset.FirstID + 1) - tileRow * tileset.ColCount - 1;

                            TextureManagerSystem::GetInstance().DrawTile(tilesetName, tileSize, tileRow, tileCol, x, y);
                        }

                        else if (tileID >= tileset.FirstID && tileID <= tileset.LastID && tileset.AnimationFrames.size() == 0)
                        {
                            int tileRow = (tileID - tileset.FirstID + 1) / tileset.ColCount;
                            int tileCol = (tileID - tileset.FirstID + 1) - tileRow * tileset.ColCount - 1;

                            TextureManagerSystem::GetInstance().DrawTile(tilesetName, tileSize, tileRow, tileCol, x, y);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void TileMapLayerComponent::Update() {

}
