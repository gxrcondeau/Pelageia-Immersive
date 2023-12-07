//
// Created by pylinskyi.k on 04.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_SHADOWMANAGER_H
#define PELAGEIA_IMMERSIVE_SHADOWMANAGER_H

#include <map>
#include <string>
#include "SDL.h"


class ShadowManager
{
public:
    static ShadowManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new ShadowManager(); }

    void DrawShadow(int offsetX, int offsetY, int playerX, int playerY, int width, int height);

private:
    ShadowManager(){};
    static ShadowManager* s_Instance;

    std::map<std::string, SDL_Rect*> m_ShadowMap;
};

#endif  // PELAGEIA_IMMERSIVE_SHADOWMANAGER_H
