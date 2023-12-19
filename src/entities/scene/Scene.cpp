//
// Created by pylinskyi.k on 19.12.2023.
//
#include "entities/scene/Scene.h"

Scene::Scene(int width, int height, int tileSize, std::vector<TilesetData> tilesets, std::vector<std::unique_ptr<BaseLayer>> layers)
    : _width(width), _height(height), _tileSize(tileSize), _tilesets(tilesets), _layers(std::move(layers)) {}

void Scene::Render() {
    for(const auto& layer: _layers){
        layer->Render();
    }
}

void Scene::Update() {
    for(auto& layer: _layers){
        layer->Update();
    }
}