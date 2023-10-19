//
// Created by admin on 16/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_ACTOR_H
#define PELAGEIA_IMMERSIVE_ACTOR_H

#include "../Graphics/Graphics.h"
#include "../Graphics/Image.h"

class Actor {
public:
    Actor(Graphics* renderer, Image* image, int x, int y);

protected:
    Graphics* Renderer;
    Image* Sprite;
    int X, Y = 0;
    float Gravity = 5.0f;
};


#endif //PELAGEIA_IMMERSIVE_ACTOR_H
