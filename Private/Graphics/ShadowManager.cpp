//
// Created by pylinskyi.k on 04.12.2023.
//

#include "Graphics/ShadowManager.h"
#include "Engine.h"

ShadowManager* ShadowManager::s_Instance = nullptr;

void ShadowManager::DrawShadow(int offsetX, int offsetY, int playerX, int playerY, int width, int height)
{
    SDL_Rect shadowRect {playerX + offsetX, playerY + offsetY, width, height};

    const auto renderer = Engine::GetInstance()->GetRenderer();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150); // Set shadow color (e.g., semi-transparent black)
    SDL_RenderFillRect(renderer, &shadowRect);

    SDL_RenderPresent(renderer);
}