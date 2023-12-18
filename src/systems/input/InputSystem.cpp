//
// Created by pylinskyi.k on 14.12.2023.
//

#include "systems/input/InputSystem.h"
#include "Engine.h"

InputSystem* InputSystem::_instance = nullptr;

void InputSystem::Listen() {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: Engine::GetInstance().Quit(); break;
            case SDL_KEYDOWN: KeyDown(); break;
            case SDL_KEYUP: KeyUp(); break;
        }
    }
}

bool InputSystem::GetKeyDown(SDL_Scancode key) {
    if (_keyStates[key] == 1) return true;
    return false;
}

void InputSystem::KeyUp() {
    _keyStates = SDL_GetKeyboardState(nullptr);
}

void InputSystem::KeyDown() {
    _keyStates = SDL_GetKeyboardState(nullptr);
}

int InputSystem::GetAxisKey(Axis axis) {
    switch (axis)
    {
        case HORIZONTAL:
            if (GetKeyDown(SDL_SCANCODE_D) || GetKeyDown(SDL_SCANCODE_RIGHT)) return 1;
            if (GetKeyDown(SDL_SCANCODE_A) || GetKeyDown(SDL_SCANCODE_LEFT)) return -1;
            return 0;

        case VERTICAL:
            if (GetKeyDown(SDL_SCANCODE_W) || GetKeyDown(SDL_SCANCODE_UP)) return 1;
            if (GetKeyDown(SDL_SCANCODE_S) || GetKeyDown(SDL_SCANCODE_DOWN)) return -1;
            return 0;
    }
}