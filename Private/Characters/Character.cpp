//
// Created by pylinskyi.k on 01.12.2023.
//

#include <valarray>
#include "Characters/Character.h"
#include "Graphics/TextureManager.h"

CharacterDirection Character::GetDirection(int horizontal, int vertical)
{
    double angle = atan2(static_cast<double>(vertical), static_cast<double>(horizontal));

    double degrees = angle * 180.0 / M_PI;

    if (degrees < 0) degrees += 360.0;

    if (degrees >= 22.5 && degrees < 67.5) return UP_RIGHT;

    else if (degrees >= 67.5 && degrees < 112.5) return UP;

    else if (degrees >= 112.5 && degrees < 157.5) return UP_LEFT;

    else if (degrees >= 157.5 && degrees < 202.5) return LEFT;

    else if (degrees >= 202.5 && degrees < 247.5) return DOWN_LEFT;

    else if (degrees >= 247.5 && degrees < 292.5) return DOWN;

    else if (degrees >= 292.5 && degrees < 337.5) return DOWN_RIGHT;

    else return RIGHT;
}