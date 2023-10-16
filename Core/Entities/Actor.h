//
// Created by admin on 16/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_ACTOR_H
#define PELAGEIA_IMMERSIVE_ACTOR_H


#include "../Graphics/Image.h"

class Actor {
public:
    Actor(Image* image, int posX, int posY);

    Image* Sprite;
    int PosX = 0;
    int PosY = 0;
};


#endif //PELAGEIA_IMMERSIVE_ACTOR_H
