//
// Created by pylinskyi.k on 02/11/2023.
//

#ifndef PELAGEIA_IMMERSIVE_INPUT_H
#define PELAGEIA_IMMERSIVE_INPUT_H

#include "SDL.h"

class Input
{
public:
    static Input* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input(); }

    void Listen();
    bool GetKeyDown(SDL_Scancode key);

private:
    Input();
    void KeyUp();
    void KeyDown();

    const Uint8* m_KeyStates;
    static Input* s_Instance;
};

#endif  // PELAGEIA_IMMERSIVE_INPUT_H
