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
#include "Animation/SpriteAnimation.h"

#define FORWARD 1
#define BACKWARD -1
#define UPWARD -1
#define DOWNWARD 1
#define JUMP_TIME = 10
#define JUMP_FORCE = 10


class Player : public Character
{
public:
    Player(std::string name, int positionRow, int positionCol, int tileSize);

    virtual void Draw() override;
    virtual void Update(float dt) override;
    virtual void Clean() override;
    virtual void HandleAnimation() override;
    virtual void HandleInput();
    virtual void HandlePhisics(float dt);
    inline bool IsInAction() { return m_IsJumping || m_IsRolling || m_IsAttacking; }

private:
    bool m_IsJumping = false;
    bool m_IsRolling = false;
    bool m_IsAttacking = false;

    float m_Velocity = 0;

    int m_HorizontalAxis;
    int m_VerticalAxis;
    float m_IsometricX;
    float m_IsometricY;

    Vector2D* m_LastSafePosition;
    Collider* m_Collider;
    RigidBody* m_RigidBody;
    SpriteAnimation* m_Animation = new SpriteAnimation();
};

#endif  // PELAGEIA_IMMERSIVE_PLAYER_H
