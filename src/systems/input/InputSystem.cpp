//
// Created by pylinskyi.k on 19.12.2023.
//
#include "systems/input/InputSystem.h"
#include "Engine.h"

InputSystem* InputSystem::_instance = nullptr;

InputSystem::InputSystem() { }

InputSystem& InputSystem::GetInstance() {
    if (!_instance) _instance = new InputSystem();
    return *_instance;
}

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
    return _keyStates[key] == 1;
}

int InputSystem::GetAxisKey(Axis axis) {
    switch (axis)
    {
        case HORIZONTAL:
            return (GetKeyDown(SDL_SCANCODE_D) || GetKeyDown(SDL_SCANCODE_RIGHT)) ? 1 :
                   (GetKeyDown(SDL_SCANCODE_A) || GetKeyDown(SDL_SCANCODE_LEFT)) ? -1 : 0;

        case VERTICAL:
            return (GetKeyDown(SDL_SCANCODE_W) || GetKeyDown(SDL_SCANCODE_UP)) ? 1 :
                   (GetKeyDown(SDL_SCANCODE_S) || GetKeyDown(SDL_SCANCODE_DOWN)) ? -1 : 0;
    }
}

void InputSystem::KeyUp() {
    _keyStates = SDL_GetKeyboardState(nullptr);
}

void InputSystem::KeyDown() {
    _keyStates = SDL_GetKeyboardState(nullptr);
}
