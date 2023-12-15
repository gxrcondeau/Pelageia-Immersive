//
// Created by pylinskyi.k on 13.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_INPUTSYSTEM_H
#define PELAGEIA_IMMERSIVE_INPUTSYSTEM_H

#include <stdexcept>
#include "SDL.h"
#include "utilities/CoreTypeEnums.h"

class InputSystem {
public:
    static InputSystem& GetInstance() {
        if (!_instance) _instance = new InputSystem();
        return *_instance;
    };

    void Listen();
    bool GetKeyDown(SDL_Scancode key);
    int GetAxisKey(Axis axis);

protected:
    InputSystem() { if (_instance) throw std::logic_error("InputSystem Instance already exists"); };

    static InputSystem* _instance;

    void KeyUp();
    void KeyDown();

    const Uint8* _keyStates;
};

#endif  // PELAGEIA_IMMERSIVE_INPUTSYSTEM_H
