//
// Created by pylinskyi.k on 05.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_SEQANIMATION_H
#define PELAGEIA_IMMERSIVE_SEQANIMATION_H

#include "Animation/Animation.h"
#include <map>
#include <vector>

struct Sequence
{
    int m_AnimSpeed;
    int m_FrameCount;

    int m_AnimSheetRows;
    int m_AnimSheetCols;
    int m_FirstSpriteRow;
    int m_FirstSpriteCol;

    uint8_t m_State;
    uint8_t m_Direction;
    SDL_RendererFlip m_Flip;
    std::vector<std::string> TextureIDs;
};

class SeqAnimation : public Animation
{
public:
    SeqAnimation() {};

    virtual void Update() override;
    void DrawFrame(
        float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, SDL_RendererFlip = SDL_FLIP_NONE);

    void SetCurrentSeq(std::string seqID) { m_CurrentSeq = m_SeqMap[seqID]; }
    void SetRepeat(bool repeat) { m_Repeat = repeat; }

private:
    Sequence m_CurrentSeq;
    std::map<std::string, Sequence> m_SeqMap;
};

#endif  // PELAGEIA_IMMERSIVE_SEQANIMATION_H
