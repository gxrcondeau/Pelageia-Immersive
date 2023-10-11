//
// Created by pylinskyi.k on 11.10.2023.
//

#include <cstdio>
#include "Game.h"

Game::Game() {
    isRunning = true;
}

int Game::Execute() {

    config = new ConfigLoader();
    WindowParams windowParams = config->getWindowParams();
    graphics = new Graphics(windowParams.name, windowParams.width, windowParams.height);

    Image* img = graphics->NewImage("Resources/dolphins.jpg");

    int x = 0;
    int y = 0;

    int directionX = 1;
    int directionY = 1;

    while(isRunning){

        graphics->DrawImage(img, x, y);
        graphics->RenderFrame();

        x += directionX;
        y += directionY;

        SDL_Delay(30);
    }

    SDL_Quit();
    return 0;
}

void Game::Exit() {
    isRunning = false;
}
