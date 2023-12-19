#ifndef PELAGEIA_IMMERSIVE_INPUTSYSTEM_H
#define PELAGEIA_IMMERSIVE_INPUTSYSTEM_H

#include "SDL.h"
#include "utilities/CoreTypeEnums.h"

class InputSystem {
public:
    static InputSystem& GetInstance();

    void Listen();
    bool GetKeyDown(SDL_Scancode key);
    int GetAxisKey(Axis axis);

protected:
    InputSystem();

    static InputSystem* _instance;

    void KeyUp();
    void KeyDown();

    const Uint8* _keyStates;
};

#endif  // PELAGEIA_IMMERSIVE_INPUTSYSTEM_H
