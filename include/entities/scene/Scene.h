//
// Created by pylinskyi.k on 19.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_SCENE_H
#define PELAGEIA_IMMERSIVE_SCENE_H

#include <vector>
#include <memory>
#include "utilities/CoreTypeStructs.h"
#include "components/scene/BaseLayer.h"

class Scene{
public:
    Scene(int width, int height, int tileSize, std::vector<TilesetData> tilesets, std::vector<std::unique_ptr<BaseLayer>> layers);

    void Render();
    void Update();

private:
    int _tileSize;
    int _width;
    int _height;
    std::vector<TilesetData> _tilesets;
    std::vector<std::unique_ptr<BaseLayer>> _layers;
};

#endif  // PELAGEIA_IMMERSIVE_SCENE_H
