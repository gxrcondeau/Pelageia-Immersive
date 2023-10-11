//
// Created by pylinskyi.k on 11.10.2023.
//

#include "Game.h"

Game::Game() {
    isRunning = true;
}

int Game::Execute() {
    while(isRunning);
    return 0;
}

void Game::Exit() {
    isRunning = false;
}
