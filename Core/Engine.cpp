//
// Created by admin on 19/10/2023.
//

#include <cstdio>
#include "Engine.h"

Engine* Engine::s_Instance = nullptr;

bool Engine::Init() {
    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0){
        SDL_Log("Failed initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("Pelageia Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 420, 0);
    if(!m_Window){
        SDL_Log("Failed initialize Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!m_Renderer){
        SDL_Log("Failed initialize Renderer: %s", SDL_GetError());
        return false;
    }

    return m_IsRunning = true;
}

bool Engine::Clean() {
    return false;
}

bool Engine::Quit() {
    return m_IsRunning = false;
}

void Engine::Update() {
    SDL_Log("Updating...");
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            Quit();
            break;
    }
}
