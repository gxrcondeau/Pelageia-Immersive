//
// Created by pylinskyi.k on 19/10/2023.
//

#include "Graphics/TextureManager.h"
#include "Camera/Camera.h"
#include "Engine.h"
#include "Graphics/ShadowManager.h"
#include "Physics/Vector2D.h"
#include "SDL.h"
#include "SDL_image.h"

bool TextureManager::LoadTexture(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface)
    {
        SDL_Log("Failed to load texture: %s %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (!texture)
    {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }
    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);

    SDL_Log("Texture %s dropped", id.c_str());
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator iterator;
    for (iterator = m_TextureMap.begin(); iterator != m_TextureMap.end(); iterator++)
    {
        SDL_DestroyTexture(iterator->second);
    }
    m_TextureMap.clear();
    SDL_Log("Texture map cleaned");
}
void TextureManager::Draw(DrawParams params)
{
    SDL_Rect srcRect = {0, 0, params.Height, params.Width};
    SDL_Rect dstRect = {params.X, params.Y, params.Height, params.Width};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[params.ID], &srcRect, &dstRect, 0, nullptr, params.Flip);
}

void TextureManager::DrawTile(DrawTileParams params)
{
    Vector2D cam = Camera::GetInstance()->GetPosition();

    int dstRectX = params.X - static_cast<int>(cam.X);
    int dstRectY = params.Y - static_cast<int>(cam.Y);

    SDL_Rect srcRect = {params.TileSize * params.Column, params.TileSize * params.Row, params.TileSize, params.TileSize};
    SDL_Rect dstRect = {dstRectX, dstRectY, params.TileSize, params.TileSize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[params.TilesetName], &srcRect, &dstRect, 0, nullptr, params.Flip);
}

void TextureManager::DrawFrame(DrawFrameParams params)
{
    if (!m_CharactersTexturesMap[params.ID])
    {
        // Handle the case where the texture for the given ID is not found or is null
        return;
    }

    Vector2D cam = Camera::GetInstance()->GetPosition();

    // Calculate the correct row and column for the frame
    int rowFrame = params.CurrentFrame / params.AnimSheetCols;
    int colFrame = params.CurrentFrame % params.AnimSheetCols;

    int srcRectX = params.SpriteWidth * (params.FirstSpriteCol) * colFrame;
    int srcRectY = params.SpriteHeight * (params.FirstSpriteRow) * rowFrame;

    int dstRectW = params.XScale * params.SpriteWidth;
    int dstRectH = params.YScale * params.SpriteHeight;

    int dstRectX = params.X - static_cast<int>(cam.X);
    int dstRectY = params.Y - static_cast<int>(cam.Y);

    SDL_Rect srcRect = {srcRectX, srcRectY, params.SpriteWidth, params.SpriteHeight};
    SDL_Rect dstRect = {dstRectX, dstRectY, dstRectW, dstRectH};

    SDL_Texture* texture = m_CharactersTexturesMap[params.ID]->StateMap[params.State]->DirectionMap[params.Direction];
    if (!texture)
    {
        SDL_Log("No texture provided  %s [%i] [%i]", params.ID.c_str(), params.State, params.Direction);
        return;
    }
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), texture, &srcRect, &dstRect, 0, nullptr, params.Flip);
}
