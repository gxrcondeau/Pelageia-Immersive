//
// Created by pylinskyi.k on 24/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_CHARACTER_H
#define PELAGEIA_IMMERSIVE_CHARACTER_H

#include "Objects/GameObject.h"

enum CharacterState
{
    IDLE,
    WALKING,
    RUNNING,
    JUMPING,
    FALLING,
    LANDING,
    CROUCHING,
    ATTACKING
};

class Character : public GameObject
{
public:
    Character(Properties* props) : GameObject(props) {}

    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;
    virtual void AnimationState() = 0;

protected:
    std::string m_Name;

    CharacterState e_CharacterState;
};

#endif  // PELAGEIA_IMMERSIVE_CHARACTER_H
