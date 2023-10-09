#ifndef PELAGEIA_IMMERSIVE_ENGINE_H
#define PELAGEIA_IMMERSIVE_ENGINE_H

#include "SDL.h"
#include <iostream>


class Engine {
public:
    Engine();

    ~Engine();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();

    void update();

    void render();

    void clean();

    bool running() { return isRunning; };

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};


#endif //PELAGEIA_IMMERSIVE_ENGINE_H
