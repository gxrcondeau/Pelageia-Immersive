//
// Created by admin on 16/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_PAWN_H
#define PELAGEIA_IMMERSIVE_PAWN_H


#include "Actor.h"

class Pawn : public Actor {
public:
    Pawn(Image* image, int posX, int posY) : Actor(image, posX, posY) {}

    void MoveRight();
    void MoveLeft();
    void MoveForward();
    void MoveBackward();

protected:
    float MovementAmount = 5.0f;
};


#endif //PELAGEIA_IMMERSIVE_PAWN_H
