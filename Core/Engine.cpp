#include "Engine.h"


Engine::Engine() {
}

Engine::~Engine() {
}


void Engine::init(const char *title) {
    ConfigLoader* config = new ConfigLoader();
    WindowParams windowParams = config->getWindowParams();

    int flags = 0;
    if (windowParams.fullScreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "All SDL2 subsystems initialized");

        window = SDL_CreateWindow(title, windowParams.xPos, windowParams.yPos, windowParams.width, windowParams.height, flags);
        if (window) {
            SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "Main window was successfully created");
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255,  255);
            SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "Renderer was successfully created" );
        }
        isRunning = true;
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "SDL2 initializing error %s", SDL_GetError());
        isRunning = false;
    }
}

void Engine::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Engine::update() {

}

void Engine::render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Engine::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game instance was cleaned" << std::endl;
}