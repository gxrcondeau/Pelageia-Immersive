#include "SDL.h"
#include "Core/Engine.h"

Engine *engine = nullptr;

int main(int argc, char *args[]) {
    engine = new Engine();
    engine->init("PEIM Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

    while(engine->running()) {
        engine->handleEvents();
        engine->update();
        engine->render();
    }

    engine->clean();
    return 0;
}
