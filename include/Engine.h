// Engine.h

#ifndef PELAGEIA_IMMERSIVE_ENGINE_H
#define PELAGEIA_IMMERSIVE_ENGINE_H

#include "SDL.h"
#include "utilities/CoreTypeStructs.h"
#include "systems/configuration/ConfigurationSystem.h"
#include "systems/input/InputSystem.h"
#include "SDL_image.h"
#include <stdexcept>

class Engine {
public:
    static Engine& GetInstance();

    SDL_Renderer* GetRenderer() const;

    bool Init();
    void Clean();
    void Quit();

    void Update();
    void Render();
    void HandleEvents();

    bool IsRunning() const;

private:
    Engine();
    static Engine* _instance;

    SDL_Window* _window;
    SDL_Renderer* _renderer;

    bool _isRunning;

    WindowData* _windowData;
};

#endif  // PELAGEIA_IMMERSIVE_ENGINE_H
