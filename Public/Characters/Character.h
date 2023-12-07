//
// Created by pylinskyi.k on 24/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_CHARACTER_H
#define PELAGEIA_IMMERSIVE_CHARACTER_H

#include <cstdint>
#include "Objects/GameObject.h"
#include "Animation/Animation.h"

enum CharacterState : std::uint8_t
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

enum CharacterDirection : std::uint8_t
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

class Character : public GameObject
{
public:
    Character(Properties* props) : GameObject(props) { m_Properties = props; }

    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;
    virtual void HandleAnimation() = 0;
    virtual CharacterDirection GetDirection(int horizontal, int vertical);

protected:
    Properties* m_Properties;
    std::string m_CharacterName;

    CharacterState m_CharacterState;
    CharacterDirection m_CharacterDirection;
};

#endif  // PELAGEIA_IMMERSIVE_CHARACTER_H
