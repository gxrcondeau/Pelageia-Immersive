//
// Created by admin on 24/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_TRANSFORM_H
#define PELAGEIA_IMMERSIVE_TRANSFORM_H

#include "Vector2D.h"

class Transform
{
public:
    Transform(float x, float y)
    {
        Origin.X = x;
        Origin.Y = y;
    }

    inline void TranslateX(float x) { Origin.X += x; };
    inline void TranslateY(float y) { Origin.Y += y; };
    inline void Translate(float x, float y)
    {
        Origin.X += x;
        Origin.Y += y;
    };
    inline void Translate(Vector2D vector) { Origin += vector; };

    Vector2D Origin;
};

#endif  // PELAGEIA_IMMERSIVE_TRANSFORM_H
