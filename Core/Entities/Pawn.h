//
// Created by admin on 16/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_PAWN_H
#define PELAGEIA_IMMERSIVE_PAWN_H


#include "Actor.h"

class Pawn : public Actor {
public:
    Pawn(Graphics* renderer, Image* image, int x, int y) : Actor(renderer, image, x, y) {}

    void Tick();

    void MoveRight();
    void MoveLeft();
    void Jump();

    void StopMoving();

    void Render();

protected:
    float MoveSpeed = 5.0f;
    float JumpHeight = 15.0f;

    float VelocityX = 0.0f;
    float MaxVelocityX = 20.0f;
    float VelocityY = 0.0f;

    bool Jumping = false;

    int Ground = 600;
};


#endif //PELAGEIA_IMMERSIVE_PAWN_H
