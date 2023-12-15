//
// Created by pylinskyi.k on 13.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_TILEMAPLAYERCOMPONENT_H
#define PELAGEIA_IMMERSIVE_TILEMAPLAYERCOMPONENT_H

#include <vector>
#include "LayerComponent.h"
#include "utilities/CoreTypeStructs.h"

class TileMapLayerComponent : LayerComponent{
public:
    TileMapLayerComponent(std::vector<TilesetData> tilesets, std::vector<std::vector<int>> tilemap);

    void Render() override;
    void Update() override;

protected:
    std::uint8_t _tileSize;
    size_t _rowCount;
    size_t _colCount;
    std::vector<TilesetData> _tilesets;
    std::vector<std::vector<int>> _tilemap;
};

#endif  // PELAGEIA_IMMERSIVE_TILEMAPLAYERCOMPONENT_H
