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
    m_CharacterName = "Player";
    m_CharacterState = IDLE;
    m_CharacterDirection = DOWN;
    m_IsJumping = false;

    m_Collider->SetBuffer(0, 0, 0, 0);
    m_Collider->Set(m_Transform->X, m_Transform->Y, 32, 32);

    m_RigidBody->SetGravity(0);

    m_Animation->SetAnimationEndCallback([this]() { m_IsJumping = false; m_IsRolling = false; });
}

void Player::Draw()
{
    const auto textureProps = TextureManager::GetInstance()->GetCharacterTextureParams(m_CharacterName);

    if (!textureProps) return;
    m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, m_Width, m_Height, textureProps->XScale, textureProps->YScale,
        textureProps->StateMap[m_CharacterState]->Flip);

    Vector2D Cam = Camera::GetInstance()->GetPosition();
    SDL_Rect Box = m_Collider->Get();
    Box.x -= Cam.X;
    Box.y -= Cam.Y;
}

void Player::Update(float dt)
{
    int tileSize = 32;

    m_RigidBody->UnsetForce();
    m_HorizontalAxis = Input::GetInstance()->GetAxisKey(HORIZONTAL);
    m_VerticalAxis = Input::GetInstance()->GetAxisKey(VERTICAL);
    m_CharacterDirection = GetDirection(m_HorizontalAxis, m_VerticalAxis);

    Vector2D inputVector(m_HorizontalAxis, -m_VerticalAxis);
    inputVector.Normalize();

    // Calculate isometric space transformation
    float isometricX = tileSize / 2 * inputVector.X;
    float isometricY = tileSize / 4 * inputVector.Y;

    if ((m_HorizontalAxis != 0 || m_VerticalAxis != 0))
    {
        m_Velocity = 0.5f;
        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && !m_IsJumping && !m_IsRolling)
        {
            m_CharacterState = JUMP;
            m_IsJumping = true;
        }
        else if (!m_IsJumping && !m_IsRolling)
            m_CharacterState = WALK;

        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LSHIFT))
        {
            if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
            {
                m_CharacterState = RUNNING_JUMP;
                m_IsJumping = true;
            }
            else if (!m_IsJumping && !m_IsRolling)
                m_CharacterState = RUN;
            m_Velocity = 1.0f;
        }

        if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LCTRL) && !m_IsJumping && !m_IsRolling)
        {
            m_CharacterState = ROLL;
            m_Velocity = 0.7f;
            m_IsRolling = true;
        }

        m_RigidBody->ApplyForceX(m_Velocity * isometricX);
        m_RigidBody->ApplyForceY(m_Velocity * isometricY);
    }
    else if (!m_IsJumping && !m_IsRolling)
    {
        m_CharacterState = IDLE;
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

    HandleAnimation();
    m_Animation->Update();
}

void Player::Clean()
{
    TextureManager::GetInstance()->Clean();
}

void Player::HandleAnimation()
{
    const auto textureProps = TextureManager::GetInstance()->GetCharacterTextureParams(m_CharacterName);

    if (textureProps && textureProps->StateMap[m_CharacterState])
    {
        m_Animation->SetTextureID(m_CharacterName);
        m_Animation->SetState(m_CharacterState);
        m_Animation->SetDirection(m_CharacterDirection);
        m_Animation->SetAnimSheetRows(textureProps->StateMap[m_CharacterState]->AnimSheetRows);
        m_Animation->SetAnimSheetCols(textureProps->StateMap[m_CharacterState]->AnimSheetCols);
        m_Animation->SetFirstSpriteRow(textureProps->StateMap[m_CharacterState]->FirstSpriteRow);
        m_Animation->SetFirstSpriteCol(textureProps->StateMap[m_CharacterState]->FirstSpriteCol);
        m_Animation->SetFrameCount(textureProps->StateMap[m_CharacterState]->FrameCount);
        m_Animation->SetAnimSpeed(textureProps->StateMap[m_CharacterState]->AnimSpeed);
        m_Animation->SetAnimSpeed(textureProps->StateMap[m_CharacterState]->AnimSpeed);
        m_Animation->SetRepeat(textureProps->StateMap[m_CharacterState]->Repeat);
        m_Animation->SetFlip(textureProps->StateMap[m_CharacterState]->Flip);
    }
}
