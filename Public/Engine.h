//
// Created by pylinskyi.k on 19/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_ENGINE_H
#define PELAGEIA_IMMERSIVE_ENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include "Map/GameMap.h"
#include "Utils/Config/ConfigLoader.h"

class Engine
{
public:
    static Engine* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine(); }

    inline SDL_Renderer* GetRenderer() { return m_Renderer; }
    inline WindowParams* GetWindowParams() { return ConfigLoader::GetInstance()->GetWindowParams(); }
    inline GameMap* GetGameMap() { return m_GameMap; }

    bool Init();
    bool Clean();
    bool Quit();

    void Update();
    void Render();
    void Events();

    inline bool IsRunning() { return m_IsRunning; }

private:
    Engine() {}
    static Engine* s_Instance;

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    GameMap* m_GameMap;

    bool m_IsRunning;
};

#endif  // PELAGEIA_IMMERSIVE_ENGINE_H
