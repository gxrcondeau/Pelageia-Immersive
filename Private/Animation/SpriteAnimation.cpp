//
// Created by pylinskyi.k on 05.12.2023.
//

#include "Animation/SpriteAnimation.h"
#include "Graphics/TextureManager.h"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat){};

void SpriteAnimation::Update()
{
    Uint32 currentTime = SDL_GetTicks();
    m_CurrentFrame = static_cast<int>((currentTime / m_AnimSpeed) % m_FrameCount);

    SDL_Log("Frame %i / %i", m_CurrentFrame, m_FrameCount);

    if (m_Repeat) {
        m_IsEnded = false;
    } else if (m_CurrentFrame == m_FrameCount - 1) {
        // Animation completed a full cycle
        m_IsEnded = true;
        SDL_Log("Animation is ended");
        if (m_IsEnded && m_AnimationEndCallback) {
            m_AnimationEndCallback();
            SDL_Log("Animation end callback");
        }
    }
}



void SpriteAnimation::DrawFrame(int x, int y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip)
{
    DrawFrameParams params;
    params.ID = m_TextureID;
    params.State = m_State;
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