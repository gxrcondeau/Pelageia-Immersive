//
// Created by admin on 19/10/2023.
//

#include "SDL.h"
#include "SDL_image.h"
#include "../Engine.h"
#include "TextureManager.h"
#include "../Physics/Vector2D.h"
#include "../Camera/Camera.h"


bool TextureManager::Load(std::string id, std::string filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(!surface){
        SDL_Log("Failed to load texture: %s %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if(!texture){
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }
    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Drop(std::string id) {
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);

    SDL_Log("Texture %s dropped", id.c_str());
}

void TextureManager::Clean() {
    std::map<std::string, SDL_Texture*>::iterator iterator;
    for(iterator = m_TextureMap.begin(); iterator != m_TextureMap.end(); iterator++){
        SDL_DestroyTexture(iterator->second);
    }
    m_TextureMap.clear();
    SDL_Log("Texture map cleaned");
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
    SDL_Rect srcRect = {0, 0, height, width};
    SDL_Rect dstRect = {x, y, height, width};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame,
                               SDL_RendererFlip flip) {
    Vector2D cam = Camera::GetInstance()->GetPosition();

    SDL_Rect srcRect = {width * frame, height * (row-1), height, width};
    SDL_Rect dstRect = {x - (int)cam.X, y - (int)cam.Y, height, width};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetName, int tileSize, int x, int y, int row, int column,
                              SDL_RendererFlip flip) {
    Vector2D cam = Camera::GetInstance()->GetPosition();

    SDL_Rect srcRect = {tileSize * column, tileSize * row, tileSize, tileSize};
    SDL_Rect dstRect = {x - (int)cam.X, y - (int)cam.Y, tileSize, tileSize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetName], &srcRect, &dstRect, 0, nullptr, flip);
}
