// Engine.cpp

#include "Engine.h"
#include "SDL_image.h"

Engine* Engine::_instance = nullptr;

Engine::Engine() : _isRunning(false), _windowData(ConfigurationSystem::GetInstance().GetWindowData()) {}

Engine& Engine::GetInstance() {
    if (!_instance) _instance = new Engine();
    return *_instance;
}

SDL_Renderer* Engine::GetRenderer() const {
    return _renderer;
}

bool Engine::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
        SDL_Log("Failed initialize SDL: %s", SDL_GetError());
        return false;
    }

    _window = SDL_CreateWindow("Pelageia Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowData->Width, _windowData->Height, 0);
    if (!_window) {
        SDL_Log("Failed initialize Window: %s", SDL_GetError());
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer) {
        SDL_Log("Failed initialize Renderer: %s", SDL_GetError());
        return false;
    }

    _isRunning = true;
    return true;
}

void Engine::Clean() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit() {
    _isRunning = false;
}

void Engine::Update() {}

void Engine::Render() {
    SDL_SetRenderDrawColor(_renderer, 255, 128, 124, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
}

void Engine::HandleEvents() {
    InputSystem::GetInstance().Listen();
}

bool Engine::IsRunning() const {
    return _isRunning;
}
