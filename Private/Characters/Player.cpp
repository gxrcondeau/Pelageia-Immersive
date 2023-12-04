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
    m_Name = "Player";
    m_IsJumping = false;
    m_IsGrounded = true;

    m_Collider->SetBuffer(0, 0, 0, 0);
    m_Collider->Set(m_Transform->X, m_Transform->Y, 32, 32);

    m_RigidBody->SetGravity(0);

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
    int HorizontalAxis = Input::GetInstance()->GetAxisKey(HORIZONTAL);
    int VerticalAxis = Input::GetInstance()->GetAxisKey(VERTICAL);

    if ((HorizontalAxis != 0 || VerticalAxis != 0) && !m_IsJumping)
    {
        float force = 5.0f;
        m_CharacterState = WALK;
        m_CharacterDirection = GetDirection(HorizontalAxis, VerticalAxis);

        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LSHIFT)){
            m_CharacterState = RUN;
            force = 10.0f;
        }

        m_RigidBody->ApplyForceX(force * HorizontalAxis);
        m_RigidBody->ApplyForceY(force * -VerticalAxis);
    }
    else if (!m_IsJumping && m_IsGrounded)
    {
        m_CharacterState = IDLE;
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && !m_IsJumping)
    {
        m_IsGrounded = false;
        m_IsJumping = true;
        auto previousState = m_CharacterState;
        m_CharacterState = previousState == RUN ? RUNNING_JUMP : JUMP;
    }
    if (!m_IsGrounded && m_JumpTime > 0)
    {
        m_JumpTime -= dt;
    }
    else
    {
        m_JumpTime = m_Properties->JumpTime;
        m_IsGrounded = true;
        m_IsJumping = false;
    }

    m_RigidBody->Update(dt);
    m_LastSafePosition->X = m_Transform->X;
    m_Transform->TranslateX(m_RigidBody->GetPosition().X);
    m_Collider->Set(m_Transform->X, m_Transform->Y, 256, 256);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) m_Transform->X = m_LastSafePosition->X;

    m_RigidBody->Update(dt);
    m_LastSafePosition->Y = m_Transform->Y;
    m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
    m_Collider->Set(m_Transform->X, m_Transform->Y, 256, 256);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) m_Transform->Y = m_LastSafePosition->Y;

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
    const auto textureProps = TextureManager::GetInstance()->GetCharacterTextureParams(m_Name);

    if (textureProps)
    {
        m_Animation->SetProps("Player", m_CharacterState, m_CharacterDirection, textureProps->AnimSheetRows, textureProps->AnimSheetCols,
            textureProps->StartSpriteRow, textureProps->FrameCount, textureProps->AnimSpeed, m_Flip);
    }
}
