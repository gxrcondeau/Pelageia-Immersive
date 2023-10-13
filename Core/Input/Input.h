//
// Created by pylinskyi.k on 12.10.2023.
//

#ifndef PELAGEIA_IMMERSIVE_INPUT_H
#define PELAGEIA_IMMERSIVE_INPUT_H


#include "SDL.h"


class Input {
private:
    SDL_Event event;

public:
    Input();
    void Update();

    SDL_MouseButtonEvent GetButtonDownCoords() const;
    bool IsMouseButtonPressed(int key) const;

    SDL_Keycode GetPressedKey() const;
    bool IsKeyPressed(const SDL_Keycode key) const;

    virtual void HandleMouseButtonDown();
    virtual void HandleMouseButtonUp();
    virtual void HandleKeyDown();
    virtual void HandleKeyUp();
    virtual void HandleQuit();
};


#endif //PELAGEIA_IMMERSIVE_INPUT_H
