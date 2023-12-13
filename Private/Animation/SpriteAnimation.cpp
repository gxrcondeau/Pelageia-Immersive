//
// Created by pylinskyi.k on 05.12.2023.
//

#include "Animation/SpriteAnimation.h"
#include "Graphics/TextureManager.h"

SpriteAnimation::SpriteAnimation() : Animation(){};

void SpriteAnimation::Update()
{
    int currentTime = SDL_GetTicks();

    if (m_CurrentState != m_PreviousState)
    {
        m_PreviousState = m_CurrentState;
        m_LastStateChangeTime = currentTime;
    }
    Uint32 elapsedTime = currentTime - m_LastStateChangeTime;
    m_CurrentFrame = static_cast<int>(elapsedTime / m_AnimSpeed) % m_FrameCount;

    if (m_CurrentFrame == m_FrameCount - 1 && m_AnimationEndCallback) m_AnimationEndCallback();
}

void SpriteAnimation::DrawFrame(int x, int y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip)
{
    DrawFrameParams params;
    params.ID = m_TextureID;
    params.State = m_CurrentState;
    params.Direction = m_Direction;
    params.X = x;
    params.Y = y;
    params.SpriteWidth = spriteWidth;
    params.SpriteHeight = spriteHeight;
    params.AnimSheetRows = m_AnimSheetRows;
    params.AnimSheetCols = m_AnimSheetCols;
    params.FirstSpriteRow = m_FirstSpriteRow;
    params.FirstSpriteCol = m_FirstSpriteCol;
    params.CurrentFrame = m_CurrentFrame;
    params.XScale = xScale;
    params.YScale = yScale;
    params.Flip = flip;
    TextureManager::GetInstance()->DrawFrame(params);
}