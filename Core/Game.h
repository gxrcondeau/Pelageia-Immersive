//
// Created by pylinskyi.k on 11.10.2023.
//

#ifndef PELAGEIA_IMMERSIVE_GAME_H
#define PELAGEIA_IMMERSIVE_GAME_H


#include "Utils/Config/ConfigLoader.h"
#include "Graphics/Graphics.h"
#include "Input/InputHandler.h"

class Game {
private:
    bool isRunning;

    ConfigLoader* config;
    Graphics* graphics;
    InputHandler* inputHandler;

public:
    Game();
    int Execute();
    void Exit();
};


#endif //PELAGEIA_IMMERSIVE_GAME_H
