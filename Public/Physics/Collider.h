//
// Created by pylinskyi.k on 21.11.2023.
//

#ifndef PELAGEIA_IMMERSIVE_COLLIDER_H
#define PELAGEIA_IMMERSIVE_COLLIDER_H


#include "SDL.h"

class Collider {
public:
    inline SDL_Rect Get() const { return m_Box; }
    inline void SetBuffer(int x, int y, int w, int h) { m_Buffer = {x, y, w, h}; }

    void Set(int x, int y, int w, int h) { m_Box = { x - m_Buffer.x, y - m_Buffer.y, w - m_Buffer.w, h - m_Buffer.h }; }

private:
    SDL_Rect m_Box;
    SDL_Rect m_Buffer;
};


#endif //PELAGEIA_IMMERSIVE_COLLIDER_H
