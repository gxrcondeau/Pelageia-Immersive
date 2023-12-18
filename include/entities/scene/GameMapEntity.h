//
// Created by pylinskyi.k on 13.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_GAMEMAPENTITY_H
#define PELAGEIA_IMMERSIVE_GAMEMAPENTITY_H

#include "components/scene/TileMapLayerComponent.h"

class GameMapEntity {
public:
    void Render() { _tileMapLayerComponent.Render(); }

    void SetTileMapLayerComponent(TileMapLayerComponent component) { _tileMapLayerComponent = component; }

private:
    TileMapLayerComponent _tileMapLayerComponent;
};

#endif  // PELAGEIA_IMMERSIVE_GAMEMAPENTITY_H
