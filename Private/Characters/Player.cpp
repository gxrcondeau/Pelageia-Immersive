//
// Created by pylinskyi.k on 24/10/2023.
//

#include "SDL.h"
#include "Characters/Player.h"
#include "Engine.h"
#include "Graphics/TextureManager.h"
#include "Inputs/Input.h"
#include "Camera/Camera.h"
#include "Collisions/CollisionHandler.h"

Player::Player(Properties* props) : Character(props)
{
    m_JumpTime = 10.f;
    m_JumpForce = 10.0f;
    m_IsJumping = false;
    m_IsGrounded = true;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0, 0, 0, 0);
    m_Collider->Set(m_Transform->X, m_Transform->Y, 32, 32);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(GRAVITY);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 10, 100);

    m_PlayerFlip = SDL_FLIP_NONE;
}

void Player::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

    Vector2D Cam = Camera::GetInstance()->GetPosition();
    SDL_Rect Box = m_Collider->Get();
    Box.x -= Cam.X;
    Box.y -= Cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &Box);
}

void Player::Update(float dt)
{
    m_RigidBody->UnsetForce();
    e_CharacterState = IDLE;

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_PlayerFlip = SDL_FLIP_HORIZONTAL;
        e_CharacterState = RUNNING;
        m_Animation->SetProps("player_anim_sheet", 4, 8, 100, m_PlayerFlip);
        m_RigidBody->ApplyForceX(5 * BACKWARD);
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_PlayerFlip = SDL_FLIP_NONE;
        e_CharacterState = RUNNING;
        m_RigidBody->ApplyForceX(5 * FORWARD);
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
    }
    if (m_IsJumping && m_JumpTime > 0)
    {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = 10.0f;
    }

    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->TranslateX(m_RigidBody->GetPosition().X);
    m_Collider->Set(m_Transform->X, m_Transform->Y, 48, 48);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) m_Transform->X = m_LastSafePosition.X;

    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
    m_Collider->Set(m_Transform->X, m_Transform->Y, 48, 48);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else
    {
        e_CharacterState = FALLING;
        m_IsGrounded = false;
    }

    m_Origin->X = m_Transform->X + m_Width / 2;
    m_Origin->Y = m_Transform->Y + m_Height / 2;

    AnimationState();
    m_Animation->Update();
}

void Player::Clean()
{
    TextureManager::GetInstance()->Clean();
}
void Player::AnimationState()
{
    switch (e_CharacterState)
    {
        case IDLE:
            m_Animation->SetProps("player_anim_sheet", 5, 6, 100, m_PlayerFlip);
            break;
        case WALKING:
            break;
        case RUNNING:
            m_Animation->SetProps("player_anim_sheet", 4, 8, 100, m_PlayerFlip);
            break;
        case JUMPING:
            m_Animation->SetProps("player_anim_sheet", 6, 8, 100, m_PlayerFlip);
            break;
        case FALLING:
            break;
        case LANDING:
            break;
        case CROUCHING:
            break;
        case ATTACKING:
            break;
    }
}
