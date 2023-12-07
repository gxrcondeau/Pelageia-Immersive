//
// Created by pylinskyi.k on 01.12.2023.
//

#include <valarray>
#include "Characters/Character.h"
#include "Graphics/TextureManager.h"

CharacterDirection Character::GetDirection(int horizontal, int vertical)
{
    // Avoid division by zero
    if (horizontal == 0 && vertical == 0) return DOWN;

    // Calculate angle in degrees using atan2
    double degrees = atan2(static_cast<double>(vertical), static_cast<double>(horizontal)) * 180.0 / M_PI;

    // Ensure degrees is positive
    if (degrees < 0) degrees += 360.0;

    // Use if-else statements to determine direction
    if (degrees >= 22.5 && degrees < 67.5) return UP_RIGHT;
    else if (degrees >= 67.5 && degrees < 112.5) return UP;
    else if (degrees >= 112.5 && degrees < 157.5) return UP_LEFT;
    else if (degrees >= 157.5 && degrees < 202.5) return LEFT;
    else if (degrees >= 202.5 && degrees < 247.5) return DOWN_LEFT;
    else if (degrees >= 247.5 && degrees < 292.5) return DOWN;
    else if (degrees >= 292.5 && degrees < 337.5) return DOWN_RIGHT;
    else return RIGHT;
}
