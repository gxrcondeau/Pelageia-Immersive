//
// Created by pylinskyi.k on 03.11.2023.
//

#include "TileLayer.h"
#include "../Graphics/TextureManager.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount,
                     TileMap tilemap, TilesetList tilesetList) : m_TilesetList(tilesize) {
    m_RowCount = rowcount;
    m_ColCount = colcount;
    m_TileMap = tilemap;

    for(unsigned i = 0; i < m_TilesetList.size(); i++){
        TextureManager::GetInstance()->Load(m_TilesetList[i].Name, "Assets/Maps/" + m_TilesetList[i].Source);
    }
}

void TileLayer::Render() {
    for(unsigned i = 0; i < m_RowCount; i++){
        for(unsigned j = 0; j < m_ColCount; j++){
            int tileID = m_TileMap[i][j];
            if(tileID == 0) continue;

            int index;
            if(m_TilesetList.size() > 1){
                for(unsigned k = 1; k < m_TilesetList.size(); k++){
                    if(tileID > m_TilesetList[k].FirstID && tileID < m_TilesetList[k].LastID){
                        tileID = tileID + m_TilesetList[k].TileCount - m_TilesetList[k].LastID;
                        index = k;
                        break;
                    }
                }
            }

            Tileset tileset = m_TilesetList[index];
            int tileRow = tileID/tileset.ColCount;
            int tileCol = tileID - tileRow * tileset.ColCount - 1;

            if(tileID % tileset.ColCount == 0){
                tileRow--;
                tileCol = tileset.ColCount - 1;
            }
        }
    }
}
