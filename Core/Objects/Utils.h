//
// Created by admin on 24/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_UTILS_H
#define PELAGEIA_IMMERSIVE_UTILS_H

#include <string>
#include "SDL.h"

struct Properties{
public:
    int X, Y;
    int Width, Height;
    std::string TextureID;
    SDL_RendererFlip Flip;

    Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip){
        TextureID = textureID;
        X = x;
        Y = y;
        Width = width;
        Height = height;
        Flip = flip;
    }
};

#endif //PELAGEIA_IMMERSIVE_UTILS_H
