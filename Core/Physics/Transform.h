//
// Created by admin on 24/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_TRANSFORM_H
#define PELAGEIA_IMMERSIVE_TRANSFORM_H


#include "Vector2D.h"

class Transform {
public:
    float X, Y;
public:
    Transform(float x, float y): X(x), Y(y) {}

    inline void TranslateX(float x) { X += x; };
    inline void TranslateY(float y) { Y += y; };
    inline void Translate(Vector2D vector) { X += vector.X; Y += vector.Y; };
};


#endif //PELAGEIA_IMMERSIVE_TRANSFORM_H
