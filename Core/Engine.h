//
// Created by admin on 19/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_ENGINE_H
#define PELAGEIA_IMMERSIVE_ENGINE_H

#include "SDL.h"
#include "SDL_image.h"

class Engine {
public:
    static Engine* GetInstance(){
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
    }

    inline SDL_Renderer* GetRenderer(){ return m_Renderer; }

    bool Init();
    bool Clean();
    bool Quit();

    void Update();
    void Render();
    void Events();

    inline bool IsRunning(){ return m_IsRunning; }
private:
    Engine() {}
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    bool m_IsRunning;
    static Engine* s_Instance;
};


#endif //PELAGEIA_IMMERSIVE_ENGINE_H
