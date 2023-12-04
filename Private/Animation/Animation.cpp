//
// Created by pylinskyi.k on 02/11/2023.
//

#include "Graphics/TextureManager.h"
#include "Animation/Animation.h"

void Animation::Update()
{
    m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, m_State, m_Direction, x, y, spriteWidth,
        spriteHeight, m_AnimSheetRows, m_AnimSheetCols, m_SpriteRow, m_SpriteFrame, m_Flip);
}

void Animation::SetProps(
    std::string textureID, uint8_t state, uint8_t direction, int animSheetRows, int animSheetCols,
    int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip)
{
    m_AnimSheetRows = animSheetRows;
    m_AnimSheetCols = animSheetCols;
    m_TextureID = textureID;
    m_State = state;
    m_Direction = direction;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
    m_Flip = flip;
}