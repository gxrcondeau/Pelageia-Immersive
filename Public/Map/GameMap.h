//
// Created by pylinskyi.k on 03.11.2023.
//

#ifndef PELAGEIA_IMMERSIVE_GAMEMAP_H
#define PELAGEIA_IMMERSIVE_GAMEMAP_H

#include <vector>
#include <map>
#include "Layer.h"
#include "TileLayer.h"

class GameMap
{
public:
    void Render()
    {
        for (auto layer : m_MapLayer)
            layer.second->Render();
        // m_MapLayer["collision"]->RenderCollision();
    }
    void Update(int dt)
    {
        for (auto layer : m_MapLayer)
            layer.second->Update(dt);
    }

    std::map<std::string, Layer*> GetMapLayers() { return m_MapLayer; }
    Layer* GetMapLayer(std::string name) { return m_MapLayer[name]; }

private:
    friend class TileMapParser;
    std::map<std::string, Layer*> m_MapLayer;
};

#endif  // PELAGEIA_IMMERSIVE_GAMEMAP_H
