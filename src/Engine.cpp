//
// Created by pylinskyi.k on 18.12.2023.
//

#include "SDL.h"
#include "SDL_image.h"
#include "systems/configuration/ConfigurationSystem.h"
#include "Engine.h"
#include "systems/scene/SceneParserSystem.h"
#include "systems/graphics/TextureManagerSystem.h"

Engine* Engine::_instance = nullptr;

Engine::Engine() {
    _windowSettings = ConfigurationSystem::GetInstance().GetWindowData();
}

bool Engine::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Failed initialize SDL: %s", SDL_GetError());
        return false;
    }

    _window = SDL_CreateWindow("Pelageia Engine", 400, 1000, _windowSettings->Width, _windowSettings->Height, 0);
    if (!_window)
    {
        SDL_Log("Failed initialize Window: %s", SDL_GetError());
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer)
    {
        SDL_Log("Failed initialize Renderer: %s", SDL_GetError());
        return false;
    }

    auto component = SceneParserSystem::GetInstance().GetTileMapLayer("map.tmx");
    _gameMap->SetTileMapLayerComponent(*component);

    TextureManagerSystem::GetInstance().LoadCharacterTextures();


//    Camera::GetInstance()->SetTarget(player->GetOrigin());
//    m_GameMap = TileMapParser::GetInstance()->GetMap("map");
    return _isRunning = true;
}

bool Engine::Clean() {
    // SceneParserSystem::GetInstance().Clear();
    TextureManagerSystem::GetInstance().ClearTextureMap();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    IMG_Quit();
    SDL_Quit();
    return false;
}
bool Engine::Quit() {
    return false;
}
void Engine::Render() {
    _gameMap->Render();
}
