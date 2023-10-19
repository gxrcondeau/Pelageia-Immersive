//
// Created by admin on 16/10/2023.
//

#include "Pawn.h"


void Pawn::Tick() {
    X += VelocityX;

    if(!Jumping){
        VelocityY += Gravity;
    }

    Y += VelocityY;

    if(Y + Sprite->GetHeight() >= Ground){
        Y = Ground - Sprite->GetHeight();

        VelocityY = 0;
        Jumping = false;
    }
}

void Pawn::MoveRight() {
    VelocityX += MoveSpeed;
}

void Pawn::MoveLeft() {
    VelocityX -= MoveSpeed;
}

void Pawn::Jump() {
    if(!Jumping){
        VelocityY = -JumpHeight;
        Jumping = true;
    }
}

void Pawn::StopMoving() {
    VelocityX = 0;
}

void Pawn::Render() {
    Renderer->DrawImage(Sprite, X, Y);
}
