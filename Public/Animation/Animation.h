//
// Created by pylinskyi.k on 02/11/2023.
//

#ifndef PELAGEIA_IMMERSIVE_ANIMATION_H
#define PELAGEIA_IMMERSIVE_ANIMATION_H

#include "SDL.h"
#include <string>

class Animation
{
public:
    Animation(){};

    void Update();
    void Draw(float x, float y, int spriteWidth, int spriteHeight);
    void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    int m_SpriteRow;
    int m_SpriteFrame;
    int m_AnimSpeed;
    int m_FrameCount;

    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};

#endif  // PELAGEIA_IMMERSIVE_ANIMATION_H
