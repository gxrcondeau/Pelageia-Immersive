//
// Created by pylinskyi.k on 12.10.2023.
//

#include "Input.h"
#include "../Utils/Logger/PeImLogger.h"


Input::Input() {

}

void Input::Update() {
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                HandleMouseButtonDown();
                break;

            case SDL_MOUSEBUTTONUP:
                HandleMouseButtonUp();
                break;

            case SDL_KEYDOWN:
                HandleKeyDown();
                break;

            case SDL_KEYUP:
                HandleKeyUp();
                break;

            case SDL_QUIT:
                break;

            default:
                HandleQuit();
                break;
        }
    }
}

SDL_MouseButtonEvent Input::GetButtonDownCoords() const{
    return event.button;
}

bool Input::IsMouseButtonPressed(int key) const{
    return event.button.button == key;
}

bool Input::IsKeyPressed(const SDL_Keycode key) const{
    return event.key.keysym.sym == key;
}

SDL_Keycode Input::GetPressedKey() const{
    return event.key.keysym.sym;
}

void Input::HandleMouseButtonDown() {
    const auto mouseCoords = GetButtonDownCoords();
    PeImLogger::Info("Mouse button pressed: [%d, %d]", mouseCoords.x, mouseCoords.y);
}

void Input::HandleMouseButtonUp() {
    const auto mouseCoords = GetButtonDownCoords();
    PeImLogger::Info("Mouse button released: [%d, %d]", mouseCoords.x, mouseCoords.y);
}

void Input::HandleKeyDown() {
    const auto key = GetPressedKey();
    PeImLogger::Info("Key pressed: [%d]", key);
}

void Input::HandleKeyUp() {
    const auto key = GetPressedKey();
    PeImLogger::Info("Key released: [%d]", key);
}

void Input::HandleQuit() {
    SDL_Quit();
    PeImLogger::Info("Quit key pressed");
}