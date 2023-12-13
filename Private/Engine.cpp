//
// Created by k.pylinskyi on 19/10/2023.
//

#include "Engine.h"
#include "Timer/Timer.h"
#include "Graphics/TextureManager.h"
#include "Characters/Player.h"
#include "Inputs/Input.h"
#include "Map/TileMapParser.h"
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

    m_Window = SDL_CreateWindow("Pelageia Engine", 400, 1000, GetWindowParams()->Width, GetWindowParams()->Height, 0);
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

    if (!TileMapParser::GetInstance()->Load())
    {
        SDL_Log("Failed to load map");
    }

    TextureManager::GetInstance()->LoadCharactersTextures();

    Properties* PlayerProps = new Properties{"Player", 0, 0, 256, 256};
    player = new Player(PlayerProps);

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    m_GameMap = TileMapParser::GetInstance()->GetMap("map");
    return m_IsRunning = true;
}

bool Engine::Clean()
{
    TileMapParser::GetInstance()->Clean();
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
    TileMapParser::GetInstance()->GetMap("map")->Update(500);
    player->Update(dt);
    Camera::GetInstance()->Update(dt);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 255, 128, 124, 255);
    SDL_RenderClear(m_Renderer);
    m_GameMap->Render();
    player->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}
