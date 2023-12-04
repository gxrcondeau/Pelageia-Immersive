//
// Created by k.pylinskyi on 19/10/2023.
//

#include "Engine.h"
#include "Timer/Timer.h"
#include "Graphics/TextureManager.h"
#include "Characters/Player.h"
#include "Inputs/Input.h"
#include "Map/MapParser.h"
#include "Camera/Camera.h"

Engine* Engine::s_Instance = nullptr;
TextureManager* TextureManager::s_Instance = nullptr;
Timer* Timer::s_Instance = nullptr;
Player* player = nullptr;

bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Failed initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow(
        "Pelageia Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GetWindowParams()->Width, GetWindowParams()->Height, 0);
    if (!m_Window)
    {
        SDL_Log("Failed initialize Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_Renderer)
    {
        SDL_Log("Failed initialize Renderer: %s", SDL_GetError());
        return false;
    }

    if (!MapParser::GetInstance()->Load())
    {
        SDL_Log("Failed to load map");
    }

    TextureManager::GetInstance()->LoadCharactersTextures();

    Properties* PlayerProps = new Properties{"Player", 256, 256, 256, 256, SDL_RendererFlip::SDL_FLIP_NONE, 10.0f, 15.0f};
    player = new Player(PlayerProps);

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    m_GameMap = MapParser::GetInstance()->GetMap("map");
    return m_IsRunning = true;
}

bool Engine::Clean()
{
    MapParser::GetInstance()->Clean();
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
    return false;
}

bool Engine::Quit()
{
    return m_IsRunning = false;
}

void Engine::Update()
{
    // Timer::GetInstance()->Tick();
    float dt = Timer::GetInstance()->GetDeltaTime();
    MapParser::GetInstance()->GetMap("map")->Update(500);
    player->Update(dt);
    Camera::GetInstance()->Update(dt);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 128, 255, 255);
    SDL_RenderClear(m_Renderer);
    TextureManager::GetInstance()->Draw("background", 0, 0, GetWindowParams()->Width, GetWindowParams()->Height);
    m_GameMap->Render();
    player->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}
