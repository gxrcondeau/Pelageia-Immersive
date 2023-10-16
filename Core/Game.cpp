//
// Created by pylinskyi.k on 11.10.2023.
//

#include <cstdio>
#include "Game.h"
#include "Utils/Logger/PeImLogger.h"
#include "Entities/Pawn.h"

Game::Game() {
    isRunning = true;
}

int Game::Execute() {

    config = new ConfigLoader();
    WindowParams windowParams = config->getWindowParams();
    graphics = new Rendering(windowParams.name, windowParams.width, windowParams.height);
    Image* img = graphics->NewImage("Resources/chelik.png");

    Pawn* player = new Pawn(img, 0, 0);

    inputHandler = new InputHandler(player);

    while(isRunning){
        inputHandler->ReadInputs();

        graphics->DrawImage(player->Sprite, player->PosX, player->PosY);

        graphics->RenderFrame();

        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}

void Game::Exit() {
    isRunning = false;
}
