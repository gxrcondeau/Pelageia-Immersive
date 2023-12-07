//
// Created by pylinskyi.k on 19/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_TEXTUREMANAGER_H
#define PELAGEIA_IMMERSIVE_TEXTUREMANAGER_H

#include "Characters/Character.h"
#include "Utils/Config/ConfigLoader.h"
#include "SDL.h"
#include <map>
#include <string>

struct DrawParams
{
    std::string ID;
    int X;
    int Y;
    int Width;
    int Height;
    SDL_RendererFlip Flip = SDL_FLIP_NONE;
};

struct DrawTileParams
{
    std::string TilesetName;
    int TileSize;
    int X;
    int Y;
    int Row;
    int Column;
    SDL_RendererFlip Flip = SDL_FLIP_NONE;
};

struct DrawFrameParams
{
    std::string ID;
    CharacterState State;
    CharacterDirection Direction;
    int X;
    int Y;
    int SpriteWidth;
    int SpriteHeight;
    int AnimSheetRows;
    int AnimSheetCols;
    int FirstSpriteRow;
    int FirstSpriteCol;
    int CurrentFrame;
    float XScale = 1;
    float YScale = 1;
    SDL_RendererFlip Flip = SDL_FLIP_NONE;
};

class TextureManager
{
public:
    static TextureManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }

    bool LoadTexture(std::string id, std::string filename);
    void LoadCharactersTextures() { m_CharactersTexturesMap = ConfigLoader::GetInstance()->GetCharactersTexturesConfig(); };
    void Drop(std::string id);
    void Clean();

    void Draw(DrawParams params);
    void DrawTile(DrawTileParams params);
    void DrawFrame(DrawFrameParams params);

    CharacterTexturesConfig* GetCharacterTextureParams(std::string id) { return m_CharactersTexturesMap[id]; }

private:
    TextureManager(){};
    std::map<std::string, SDL_Texture*> m_TextureMap;
    std::map<std::string, CharacterTexturesConfig*> m_CharactersTexturesMap;
    static TextureManager* s_Instance;
};

#endif  // PELAGEIA_IMMERSIVE_TEXTUREMANAGER_H
