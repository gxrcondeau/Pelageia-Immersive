//
// Created by pylinskyi.k on 14.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_CORETYPESTRUCTS_H
#define PELAGEIA_IMMERSIVE_CORETYPESTRUCTS_H

#include <map>
#include <vector>
#include <string>
#include "SDL_render.h"
#include "utilities/CoreTypeEnums.h"
#include "../../Vendor/SDL/include/SDL2/SDL_render.h"

struct WindowData
{
    std::string Name;
    int Width;
    int Height;
    bool IsFullScreen;
    bool IsIsometric;
};

struct StaticTextureData {
    int Width;
    int Height;
    SDL_RendererFlip Flip;
    SDL_Texture* Texture;
};

struct StateTextureData {
    int AnimSheetRows;
    int AnimSheetCols;
    int FirstSpriteRow;
    int FirstSpriteCol;
    int FrameCount;
    int AnimSpeed;
    bool Repeat;
    SDL_RendererFlip Flip;
    std::map<Direction, SDL_Texture*> Directions;
};

struct CharacterSpriteData {
    int Width;
    int Height;
    double XScale;
    double YScale;
    std::map<State, StateTextureData*> States;
};

struct TilesetData {
    std::string Name;
    int FirstID;
    int LastID;
    int RowCount;
    int ColCount;
    int TileCount;
    int TileSize;
    std::string Source;
    std::vector<int> AnimationFrames;
};

struct LayerData {
    std::string Name;
    int Width;
    int Height;
    std::vector<std::vector<int>> Map;
};

#endif  // PELAGEIA_IMMERSIVE_CORETYPESTRUCTS_H
