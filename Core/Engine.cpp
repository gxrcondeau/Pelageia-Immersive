//
// Created by admin on 19/10/2023.
//

#include <cstdio>
#include "Engine.h"
#include "Timer/Timer.h"
#include "Graphics/TextureManager.h"
#include "Objects/Utils.h"
#include "Characters/Player.h"
#include "Inputs/Input.h"
#include "Map/MapParser.h"
#include "Camera/Camera.h"


Engine* Engine::s_Instance = nullptr;
TextureManager* TextureManager::s_Instance = nullptr;
Timer* Timer::s_Instance = nullptr;

Player* player = nullptr;

bool Engine::Init() {
    m_WindowParams = GetWindowParams();

    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0){
        SDL_Log("Failed initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("Pelageia Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowParams->Width, m_WindowParams->Height, 0);
    if(!m_Window){
        SDL_Log("Failed initialize Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!m_Renderer){
        SDL_Log("Failed initialize Renderer: %s", SDL_GetError());
        return false;
    }

    if(!MapParser::GetInstance()->Load()){
        SDL_Log("Failed to load map");
    }

    TextureManager::GetInstance()->Load("player_idle", "Resources/Animations/Player/player_idle.png");
    TextureManager::GetInstance()->Load("player_run", "Resources/Animations/Player/player_run.png");
    TextureManager::GetInstance()->Load("background", "Resources/BackGround/NonParallax.png");
    player = new Player(new Properties("player_idle", 240, 120, 48, 48, SDL_RendererFlip::SDL_FLIP_NONE));
    Camera::GetInstance()->SetTarget(player->GetOrigin());

    return m_IsRunning = true;
}

bool Engine::Clean() {
    MapParser::GetInstance()->Clean();
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
    return false;
}

bool Engine::Quit() {
    return m_IsRunning = false;
}

void Engine::Update() {
    //Timer::GetInstance()->Tick();
    float dt = Timer::GetInstance()->GetDeltaTime();
    MapParser::GetInstance()->GetMap("map")->Update(500);
    player->Update(dt);
    Camera::GetInstance()->Update(dt);
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 124, 128, 255, 255);
    SDL_RenderClear(m_Renderer);
    TextureManager::GetInstance()->Draw("background", 0, 0, m_WindowParams->Width, m_WindowParams->Height);
    MapParser::GetInstance()->GetMap("map")->Render();
    player->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {
    Input::GetInstance()->Listen();
}
