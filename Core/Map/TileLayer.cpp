//
// Created by pylinskyi.k on 03.11.2023.
//

#include <iostream>
#include "TileLayer.h"
#include "../Graphics/TextureManager.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesetList) :
        m_TileSize(tilesize), m_RowCount(rowcount), m_ColCount(colcount), m_TileMap(tilemap), m_TilesetList(tilesetList) {
    for(auto tilesetList: m_TilesetList)
        TextureManager::GetInstance()->Load(tilesetList.Name, "Assets/Maps/" + tilesetList.Source);
}

void TileLayer::Render() {
    for (unsigned row = 0; row < m_RowCount; row++){
        for (unsigned col = 0; col < m_ColCount; col++){
            int tileID = m_TileMap[row][col];

            if (tileID > 0){
                for(auto tileset: m_TilesetList){
                    std::string tilesetName = tileset.Name;
                    int tileSize = tileset.TileSize;
                    int x = col * tileset.TileSize;
                    int y = row * tileset.TileSize;

                    // Tile Animation for some reason render not working in update function
                    if (tileset.Animation.size() > 0 && tileID == tileset.Animation[0].FrameID) {
                        int frame = (SDL_GetTicks() / 100) % tileset.Animation.size();

                        int tileRow = (tileset.Animation[frame].FrameID - tileset.FirstID + 1) / tileset.ColCount;
                        int tileCol = (tileset.Animation[frame].FrameID - tileset.FirstID + 1) - tileRow * tileset.ColCount - 1;

                        TextureManager::GetInstance()->DrawTile(tilesetName, tileSize, x, y, tileRow, tileCol);
                    }
                    // Static Tile render
                    else if(tileID >= tileset.FirstID && tileID <= tileset.LastID && tileset.Animation.size() == 0){
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

// Animated tiles render
void TileLayer::Update(int dt) {

}
