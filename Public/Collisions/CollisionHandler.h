//
// Created by pylinskyi.k on 21.11.2023.
//

#ifndef PELAGEIA_IMMERSIVE_COLLISIONHANDLER_H
#define PELAGEIA_IMMERSIVE_COLLISIONHANDLER_H

#include <SDL.h>
#include <vector>
#include "Map/TileLayer.h"
#include "Map/GameMap.h"
#include "Engine.h"

class CollisionHandler
{
public:
    static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr ? s_Instance : new CollisionHandler()); }

    bool CheckCollision(SDL_Rect a, SDL_Rect b);
    bool MapCollision(SDL_Rect a);

private:
    CollisionHandler();
    TileMap m_CollisionTilemap;
    TileLayer* m_CollisionLayer;

    static CollisionHandler* s_Instance;
};

#endif  // PELAGEIA_IMMERSIVE_COLLISIONHANDLER_H
