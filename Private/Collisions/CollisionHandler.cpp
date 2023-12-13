//
// Created by pylinskyi.k on 21.11.2023.
//

#include "Collisions/CollisionHandler.h"
#include "Physics/Vector2D.h"
#include "Camera/Camera.h"
#include "Graphics/TextureManager.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetGameMap()->GetMapLayers()["collision"];
    m_CollisionTilemap = m_CollisionLayer->GetTilemap();
    m_TileSize = m_CollisionLayer->GetTileSize();
    m_RowCount = m_CollisionLayer->GetRowCount();
    m_ColCount = m_CollisionLayer->GetColCount();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = (a.x < b.x + b.w) && (b.x < a.x + a.w);
    bool y_overlaps = (a.y < b.y + b.h) && (b.y < a.y + a.h);

    return x_overlaps && y_overlaps;
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    for (unsigned row = 0; row < m_RowCount; row++)
    {
        for (unsigned col = 0; col < m_ColCount; col++)
        {
            int tileID = m_CollisionTilemap[row][col];

            if (tileID > 0)
            {

                int x = (col - row) * (m_TileSize / 2);
                int y = (col + row) * (m_TileSize / 4);

                TextureManager::GetInstance()->DrawCollision(x, y);
            }
        }
    }

    return false;
}