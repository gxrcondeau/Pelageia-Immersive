//
// Created by pylinskyi.k on 03.11.2023.
//

#ifndef PELAGEIA_IMMERSIVE_TILELAYER_H
#define PELAGEIA_IMMERSIVE_TILELAYER_H

#include "Layer.h"
#include <string>
#include <vector>

struct TileAnimation{
    int FrameID, Duration;
};

struct Tileset{
    int FirstID, LastID;
    int RowCount, ColCount;
    int TileCount, TileSize;
    std::string Name, Source;
    std::vector<TileAnimation> Animation;
};



using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;


class TileLayer : public Layer{
public:
    TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesetList);

    void Render() override;
    void Update(int dt) override;

    inline TileMap GetTilemap() { return m_TileMap; }
    inline int GetTileSize() { return m_TileSize; }
    inline int GetRowCount() { return m_RowCount; }
    inline int GetColCount() { return m_ColCount; }
private:
    int m_TileSize;
    int m_RowCount, m_ColCount;
    TileMap m_TileMap;
    TilesetList m_TilesetList;
};


#endif //PELAGEIA_IMMERSIVE_TILELAYER_H
