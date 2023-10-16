//
// Created by pylinskyi.k on 12.10.2023.
//

#ifndef PELAGEIA_IMMERSIVE_INPUTHANDLER_H
#define PELAGEIA_IMMERSIVE_INPUTHANDLER_H


#include "SDL.h"
#include "../Entities/Pawn.h"


class InputHandler {
public:
    InputHandler(Pawn* pawn);

    void ReadInputs();

    SDL_MouseButtonEvent GetButtonDownCoords(SDL_Event event);
    bool IsMouseButtonPressed(SDL_Event event, int key);

    SDL_Keycode GetPressedKey(SDL_Event event);
    bool IsKeyPressed(SDL_Event event, SDL_Keycode key);

    virtual void HandleMouseButtonDown(SDL_Event event);
    virtual void HandleMouseButtonUp(SDL_Event event);
    virtual void HandleKeyDown(SDL_Event event);
    virtual void HandleKeyUp(SDL_Event event);
    virtual void HandleQuit(SDL_Event event);

protected:
    Pawn* Player;
};


#endif //PELAGEIA_IMMERSIVE_INPUTHANDLER_H
