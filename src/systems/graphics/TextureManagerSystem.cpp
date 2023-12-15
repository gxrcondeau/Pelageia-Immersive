//
// Created by pylinskyi.k on 14.12.2023.
//

#include "SDL_image.h"
#include "Engine.h"
#include "systems/graphics/TextureManagerSystem.h"

TextureManagerSystem* TextureManagerSystem::_instance = nullptr;

bool TextureManagerSystem::LoadTexture(std::string id, std::string source, SDL_RendererFlip flip) {
    SDL_Surface* surface = IMG_Load(source.c_str());
    if (!surface) {
        SDL_Log("Failed to load texture: %s %s", source.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance().GetRenderer(), surface);
    if (!texture) {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        SDL_FreeSurface(surface); // Free surface in case of failure
        return false;
    }

    std::unique_ptr<StaticTextureData> textureData = std::make_unique<StaticTextureData>();
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    textureData->Width = width;
    textureData->Height = height;
    textureData->Flip = flip;
    textureData->Texture = texture;

    _textureMap[id] = std::move(textureData);
    SDL_DestroyTexture(texture);
    return true;
}


void TextureManagerSystem::Draw(std::string id, int x, int y) {
    const auto it = _textureMap.find(id);
    if (it == _textureMap.end()) return;
    std::unique_ptr<StaticTextureData>& texture = it->second;

    if (!texture) return;

    SDL_Rect srcRect = {0, 0, texture->Height, texture->Width};
    SDL_Rect dstRect = {x, y, texture->Height, texture->Width};
    SDL_RenderCopyEx(Engine::GetInstance().GetRenderer(), texture->Texture, &srcRect, &dstRect, 0, nullptr, texture->Flip);
}

void TextureManagerSystem::DrawTile(std::string id, int tileSize, int row, int col, int x, int y) {
    const auto it = _textureMap.find(id);
    if (it == _textureMap.end()) return;
    std::unique_ptr<StaticTextureData>& texture = it->second;

    if (!texture) return;

    SDL_Rect srcRect = {tileSize * col, tileSize * row, tileSize, tileSize};
    SDL_Rect dstRect = {x, y, tileSize, tileSize};
    SDL_RenderCopyEx(Engine::GetInstance().GetRenderer(), texture->Texture, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
}

void TextureManagerSystem::DrawFrame(std::string id, State state, Direction direction, int frame, int x, int y) {
    const auto it = _spriteMap.find(id);
    if (it == _spriteMap.end()) return;

    std::unique_ptr<CharacterSpriteData>& characterSprite = it->second;
    if (!characterSprite) return;

    auto stateIt = characterSprite->States.find(state);
    if (stateIt == characterSprite->States.end()) return;

    const auto stateTextureData = stateIt->second;
    if (!stateTextureData) return;

    int srcRectX = stateTextureData->FirstSpriteCol * (frame % stateTextureData->AnimSheetCols);
    int srcRectY = stateTextureData->FirstSpriteRow * (frame / stateTextureData->AnimSheetCols);

    int dstRectW = characterSprite->XScale * stateTextureData->AnimSheetCols;
    int dstRectH = characterSprite->YScale * stateTextureData->AnimSheetRows;

    SDL_Rect srcRect = { srcRectX, srcRectY, stateTextureData->AnimSheetCols, stateTextureData->AnimSheetRows };
    SDL_Rect dstRect = { x, y, dstRectW, dstRectH };

    const auto texture = stateTextureData->Directions[direction];
    if (!texture)
    {
        SDL_Log("No texture provided  %s [%i] [%i]", id.c_str(), state, direction);
        return;
    }
    SDL_RenderCopyEx(Engine::GetInstance().GetRenderer(), texture, &srcRect, &dstRect, 0, nullptr, stateTextureData->Flip);
}


void TextureManagerSystem::DropTexture(std::string id) {
    SDL_DestroyTexture(_textureMap[id]->Texture);
    _textureMap.erase(id);

    SDL_Log("Texture %s dropped", id.c_str());
}

void TextureManagerSystem::ClearTextureMap() {
    for (auto it = _textureMap.begin(); it != _textureMap.end(); ++it)
    {
        DropTexture(it->first);
    }
    _textureMap.clear();

    SDL_Log("Texture map cleaned");
}
