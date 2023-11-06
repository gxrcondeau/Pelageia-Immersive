//
// Created by pylinskyi.k on 03.11.2023.
//

#ifndef PELAGEIA_IMMERSIVE_TILELAYER_H
#define PELAGEIA_IMMERSIVE_TILELAYER_H

#include "Layer.h"
#include <string>
#include <vector>


struct Tileset{
    int First, LastID;
    int NumRows, NumCols;
    int TileCount, TileSize;
    std::string Name, Source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer : public Layer{
public:
    TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesetList);

    virtual void Render() = 0;
    virtual void Update() = 0;

    inline TileMap GetTilemap() { return m_TileMap; }
private:
    int m_TileSize;
    int m_RowCount, m_ColCount;
    TileMap m_TileMap;
    TilesetList m_TilesetList;
};


#endif //PELAGEIA_IMMERSIVE_TILELAYER_H
