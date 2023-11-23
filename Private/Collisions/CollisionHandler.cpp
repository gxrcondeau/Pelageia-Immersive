//
// Created by pylinskyi.k on 21.11.2023.
//

#include "Collisions/CollisionHandler.h"
#include "Physics/Vector2D.h"
#include "Camera/Camera.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetGameMap()->GetMapLayers().front();
    m_CollisionTilemap = m_CollisionLayer->GetTilemap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = (a.x < b.x + b.w) && (b.x < a.x + a.w);
    bool y_overlaps = (a.y < b.y + b.h) && (b.y < a.y + a.h);

    return x_overlaps && y_overlaps;
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    int tileSize = m_CollisionLayer->GetTileSize();
    int rowCount = m_CollisionLayer->GetRowCount();
    int colCount = m_CollisionLayer->GetColCount();

    int left_tile = a.x / tileSize;
    int right_tile = (a.x + a.w) / tileSize;

    int top_tile = a.y / tileSize;
    int bottom_tile = (a.y + a.h) / tileSize;

    if (left_tile < 0) left_tile = 0;
    if (right_tile > colCount) right_tile = colCount;

    if (top_tile < 0) top_tile = 0;
    if (bottom_tile > rowCount) bottom_tile = rowCount;

    for (int i = left_tile; i < right_tile; i++)
    {
        for (int j = top_tile; j < bottom_tile; j++)
        {
            if (m_CollisionTilemap[j][i] > 0) return true;
        }
    }

    return false;
}