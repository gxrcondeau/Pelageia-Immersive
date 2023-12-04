//
// Created by pylinskyi.k on 19/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_TEXTUREMANAGER_H
#define PELAGEIA_IMMERSIVE_TEXTUREMANAGER_H

#include "SDL.h"
#include "Characters/Character.h"
#include <string>
#include <map>

struct CharacterTextureParams
{
    std::uint8_t AnimSheetRows;
    std::uint8_t AnimSheetCols;
    std::uint8_t StartSpriteRow;
    std::uint8_t FrameCount;
    std::uint8_t AnimSpeed;
    SDL_RendererFlip Flip;
    std::map<CharacterState, std::map<CharacterDirection, SDL_Texture*>> TextureMap;
};

class TextureManager
{
public:
    static TextureManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }

    bool LoadTexture(std::string id, std::string filename);
    bool LoadCharactersTextures();
    void Drop(std::string id);
    void Clean();

    void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawTile(std::string tilesetName, int tileSize, int x, int y, int row, int column, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawFrame(std::string id, uint8_t state, uint8_t direction, int x, int y, int width, int height,
        int animSheetRows, int animSheetCols, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

    CharacterTextureParams* GetCharacterTextureParams(std::string id) { return m_CharactersTextureParams[id]; }

private:
    TextureManager(){};
    std::map<std::string, SDL_Texture*> m_TextureMap;
    std::map<std::string, CharacterTextureParams*> m_CharactersTextureParams;
    static TextureManager* s_Instance;
};

#endif  // PELAGEIA_IMMERSIVE_TEXTUREMANAGER_H
