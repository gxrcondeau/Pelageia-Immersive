#include "SDL.h"
#include "Core/Engine.h"
#include "Core/Utils/ConfigLoader.h"

Engine *engine = nullptr;
ConfigLoader *config = nullptr;

int main(int argc, char *args[]) {
    engine = new Engine();
    config = new ConfigLoader();
    std::cout << "Loading config" << std::endl;
    config->getXml();
    std::cout << "Config loaded" << std::endl;
     engine->init("PEIM Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

    while(engine->running()) {
        engine->handleEvents();
        engine->update();
        engine->render();
    }

    engine->clean();
    return 0;
}
