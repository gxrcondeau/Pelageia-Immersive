//
// Created by pylinskyi.k on 19/10/2023.
//

#include "SDL.h"
#include "SDL_image.h"
#include "Engine.h"
#include "Graphics/TextureManager.h"
#include "Physics/Vector2D.h"
#include "Camera/Camera.h"

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

bool TextureManager::LoadCharactersTextures()
{
    std::map<std::string, CharacterTexturesConfig*> config = ConfigLoader::GetInstance()->GetCharactersTexturesConfig();

    for (auto character = config.begin(); character != config.end(); character++)
    {
        if (!m_CharactersTextureParams[character->first]) m_CharactersTextureParams[character->first] = new CharacterTextureParams();

        m_CharactersTextureParams[character->first]->AnimSheetRows = character->second->AnimSheetRows;
        m_CharactersTextureParams[character->first]->AnimSheetCols = character->second->AnimSheetCols;
        m_CharactersTextureParams[character->first]->StartSpriteRow = character->second->StartSpriteRow;
        m_CharactersTextureParams[character->first]->FrameCount = character->second->FrameCount;
        m_CharactersTextureParams[character->first]->AnimSpeed = character->second->AnimSpeed;
        m_CharactersTextureParams[character->first]->Flip = character->second->Flip;

        for (auto state = character->second->TextureMap.begin(); state != character->second->TextureMap.end(); state++)
        {
            for (auto direction = state->second.begin(); direction != state->second.end(); direction++)
            {
                SDL_Surface* surface = IMG_Load( direction->second.c_str());
                if (!surface)
                {
                    SDL_Log("Failed to load texture: %s %s", direction->second.c_str(), SDL_GetError());
                    return false;
                }

                SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
                if (!texture)
                {
                    SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
                    return false;
                }

                m_CharactersTextureParams[character->first]->TextureMap[state->first][direction->first] = texture;
            }
        }

        return true;
    }
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

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, height, width};
    SDL_Rect dstRect = {x, y, height, width};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(
    std::string id, uint8_t state, uint8_t direction, int x, int y, int width, int height, int animSheetRows, int animSheetCols, int row, int frame, SDL_RendererFlip flip)
{
    if (!m_CharactersTextureParams[id]) return;

    Vector2D cam = Camera::GetInstance()->GetPosition();

    int rowFrame = frame % animSheetCols;
    int colFrame = frame % animSheetRows;
    SDL_Rect srcRect = {width * rowFrame, height * (row - 1) * colFrame, height, width};
    SDL_Rect dstRect = {x - (int)cam.X, y - (int)cam.Y, height, width};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_CharactersTextureParams[id]->TextureMap[static_cast<CharacterState>(state)][static_cast<CharacterDirection>(direction)], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetName, int tileSize, int x, int y, int row, int column, SDL_RendererFlip flip)
{
    Vector2D cam = Camera::GetInstance()->GetPosition();

    SDL_Rect srcRect = {tileSize * column, tileSize * row, tileSize, tileSize};
    SDL_Rect dstRect = {x - (int)cam.X, y - (int)cam.Y, tileSize, tileSize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetName], &srcRect, &dstRect, 0, nullptr, flip);
}

