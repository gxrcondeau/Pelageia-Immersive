//
// Created by pylinskyi.k on 14.12.2023.
//

#ifndef PELAGEIA_IMMERSIVE_CORETYPEENUMS_H
#define PELAGEIA_IMMERSIVE_CORETYPEENUMS_H

#include <cstdint>

enum State : std::uint8_t
{
    IDLE = 0,
    WALK = 1,
    RUN = 2,
    JUMP = 3,
    RUNNING_JUMP = 4,
    ROLL = 5,
    MELEE_ATTACK = 6,
    BLOCK = 7,
    PUSH = 8,
    DAMAGE = 9,
    DEATH = 10
};

enum Direction : std::uint8_t
{
    UP = 0,
    UP_RIGHT = 1,
    RIGHT = 2,
    DOWN_RIGHT = 3,
    DOWN = 4,
    DOWN_LEFT = 5,
    LEFT = 6,
    UP_LEFT = 7
};

enum Axis
{
    HORIZONTAL,
    VERTICAL
};

enum class LayerType : std::uint8_t {
    TILE = 0,
    OBJECT = 1,
    CHARACTER = 2,
    COLLISION = 3,
    DECORATION = 4,
    EVENT = 5,
    EFFECT = 6,
    OVERLAY = 7
};

#endif  // PELAGEIA_IMMERSIVE_CORETYPEENUMS_H
