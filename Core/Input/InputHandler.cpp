//
// Created by pylinskyi.k on 12.10.2023.
//

#include "InputHandler.h"
#include "../Utils/Logger/PeImLogger.h"


InputHandler::InputHandler(Pawn* pawn) {
    Player = pawn;
}

SDL_MouseButtonEvent InputHandler::GetButtonDownCoords(SDL_Event event){
    return event.button;
}

bool InputHandler::IsMouseButtonPressed(SDL_Event event, int key){
    return event.button.button == key;
}

bool InputHandler::IsKeyPressed(SDL_Event event, const SDL_Keycode key){
    return event.key.keysym.sym == key;
}

SDL_Keycode InputHandler::GetPressedKey(SDL_Event event){
    return event.key.keysym.sym;
}

void InputHandler::HandleMouseButtonDown(SDL_Event event) {
    const auto mouseCoords = GetButtonDownCoords(event);
    PeImLogger::Info("Mouse button pressed: [%d, %d]", mouseCoords.x, mouseCoords.y);
}

void InputHandler::HandleMouseButtonUp(SDL_Event event) {
    const auto mouseCoords = GetButtonDownCoords(event);
    PeImLogger::Info("Mouse button released: [%d, %d]", mouseCoords.x, mouseCoords.y);
}

void InputHandler::HandleKeyDown(SDL_Event event) {
    const auto key = GetPressedKey(event);
    PeImLogger::Info("Key pressed: [%d]", key);

    switch(key){
        case SDLK_SPACE:
            Player->Jump();
            break;
        case SDLK_LEFT:
            Player->MoveLeft();
            break;
        case SDLK_RIGHT:
            Player->MoveRight();
            break;
        case SDLK_ESCAPE:
            HandleQuit(event);
    }
}

void InputHandler::HandleKeyUp(SDL_Event event) {
    const auto key = GetPressedKey(event);
    PeImLogger::Info("Key released: [%d]", key);

    switch(key){
        case SDLK_LEFT:
            Player->StopMoving();
            break;
        case SDLK_RIGHT:
            Player->StopMoving();
            break;
    }
}

void InputHandler::HandleQuit(SDL_Event event) {
    PeImLogger::Info("Quit key pressed");
    SDL_Quit();
}

void InputHandler::ReadInputs() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                HandleMouseButtonDown(event);
                break;

            case SDL_MOUSEBUTTONUP:
                HandleMouseButtonUp(event);
                break;

            case SDL_KEYDOWN:
                HandleKeyDown(event);
                break;

            case SDL_KEYUP:
                HandleKeyUp(event);
                break;

            case SDL_QUIT:
                HandleQuit(event);
                break;
        }
    }
}

