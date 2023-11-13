//
// Created by pylinskyi.k on 03.11.2023.
//

#include <iostream>
#include "TileLayer.h"
#include "../Graphics/TextureManager.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesetList) :
        m_TileSize(tilesize), m_RowCount(rowcount), m_ColCount(colcount), m_TileMap(tilemap), m_TilesetList(tilesetList) {
    for(unsigned i = 0; i < m_TilesetList.size(); i++){
        TextureManager::GetInstance()->Load(m_TilesetList[i].Name, "Assets/Maps/" + m_TilesetList[i].Source);
    }
}

void TileLayer::Render() {
    for (unsigned row = 0; row < m_RowCount; row++){
        for (unsigned col = 0; col < m_ColCount; col++){
            int tileID = m_TileMap[row][col];

            if (tileID > 0){
                for(auto tileset: m_TilesetList){

                    if (tileID >= tileset.FirstID && tileID <= tileset.LastID){
                        std::string tilesetName = tileset.Name;
                        int tileSize = tileset.TileSize;
                        int x = col * tileset.TileSize;
                        int y = row * tileset.TileSize;

                        int tileRow = (tileID - tileset.FirstID + 1)/tileset.ColCount;
                        int tileCol = (tileID - tileset.FirstID + 1) - tileRow * tileset.ColCount - 1;

                        TextureManager::GetInstance()->DrawTile(tilesetName, tileSize, x, y,tileRow, tileCol);
                        break;
                    }
                }
            }
        }
    }
}

void TileLayer::Update() {
    SDL_Log("Updating layer");
}
