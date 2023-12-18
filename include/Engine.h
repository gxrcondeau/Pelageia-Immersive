//
// Created by pylinskyi.k on 15.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_ENGINE_H
#define PELAGEIA_IMMERSIVE_ENGINE_H

#include "SDL.h"
#include "utilities/CoreTypeStructs.h"
#include "entities/scene/GameMapEntity.h"
#include <stdexcept>

class Engine {
public:
    static Engine& GetInstance() {
        if (!_instance) _instance = new Engine();
        return *_instance;
    }

    inline SDL_Renderer* GetRenderer() { return _renderer; }

    bool Init();
    bool Clean();
    bool Quit();

    void Update();
    void Render();
    void Events();

    inline bool IsRunning() { return _isRunning; }

private:
    Engine();
    static Engine* _instance;

    SDL_Window* _window;
    SDL_Renderer* _renderer;

    bool _isRunning;

    GameMapEntity* _gameMap;

    WindowData* _windowSettings;
    std::map<std::string, StaticTextureData*> _staticTextureMap;
    std::map<std::string, CharacterSpriteData*> _characterSpriteMap;
};

#endif  // PELAGEIA_IMMERSIVE_ENGINE_H
