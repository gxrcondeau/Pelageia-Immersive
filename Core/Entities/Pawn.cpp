//
// Created by admin on 16/10/2023.
//

#include "Pawn.h"

void Pawn::MoveRight() {
    PosX += MovementAmount;
}

void Pawn::MoveLeft() {
    PosX -= MovementAmount;
}

void Pawn::MoveForward() {
    PosY -= MovementAmount;
}

void Pawn::MoveBackward() {
    PosY += MovementAmount;
}
