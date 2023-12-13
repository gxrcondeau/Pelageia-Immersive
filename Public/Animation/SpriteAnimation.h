//
// Created by pylinskyi.k on 05.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_SPRITEANIMATION_H
#define PELAGEIA_IMMERSIVE_SPRITEANIMATION_H

#include "Animation/Animation.h"

class SpriteAnimation : public Animation
{
public:
    SpriteAnimation();

    void Update() override;

    void DrawFrame(int x, int y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip);

    void SetTextureID(std::string textureID) { m_TextureID = textureID; }
    void SetState(CharacterState state)
    {
        m_PreviousState = m_CurrentState;
        m_CurrentState = state;
    }
    void SetDirection(CharacterDirection direction) { m_Direction = direction; }

    void SetAnimSheetRows(int rows) { m_AnimSheetRows = rows; }
    void SetAnimSheetCols(int cols) { m_AnimSheetCols = cols; }

    void SetFirstSpriteRow(int row) { m_FirstSpriteRow = row; }
    void SetFirstSpriteCol(int col) { m_FirstSpriteCol = col; }

    void SetFrameCount(int count) { m_FrameCount = count; }
    void SetAnimSpeed(int speed) { m_AnimSpeed = speed; }
    void SetFlip(SDL_RendererFlip flip) { m_Flip = flip; }
    void SetRepeat(bool repeat) { m_Repeat = repeat; }

private:
    int m_CurrentFrame;
    int m_AnimSpeed;
    int m_FrameCount;

    int m_AnimSheetRows;
    int m_AnimSheetCols;
    int m_FirstSpriteRow;
    int m_FirstSpriteCol;

    std::string m_TextureID;
    CharacterState m_CurrentState;
    CharacterState m_PreviousState;
    int m_LastStateChangeTime;
    CharacterDirection m_Direction;
    SDL_RendererFlip m_Flip;
};

#endif  // PELAGEIA_IMMERSIVE_SPRITEANIMATION_H
