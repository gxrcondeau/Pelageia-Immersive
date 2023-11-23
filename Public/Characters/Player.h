//
// Created by pylinskyi.k on 24/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_PLAYER_H
#define PELAGEIA_IMMERSIVE_PLAYER_H

#include "Character.h"
#include "Physics/Vector2D.h"
#include "Physics/RigidBody.h"
#include "Animation/Animation.h"
#include "Physics/Collider.h"

#define FORWARD 1
#define BACKWARD -1
#define UPWARD -1
#define DOWNWARD 1
#define JUMP_TIME = 10
#define JUMP_FORCE = 10

class Player : public Character
{
public:
    Player(Properties* props);

    virtual void Draw() override;
    virtual void Update(float dt) override;
    virtual void Clean() override;

private:
    bool m_IsJumping;
    bool m_IsGrounded;

    float m_JumpTime;
    float m_JumpForce;

    Collider* m_Collider;
    Animation* m_Animation;
    RigidBody* m_RigidBody;
    Vector2D m_LastSafePosition;
    SDL_RendererFlip m_PlayerFlip;
};

#endif  // PELAGEIA_IMMERSIVE_PLAYER_H
