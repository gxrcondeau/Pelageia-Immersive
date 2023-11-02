//
// Created by admin on 24/10/2023.
//

#include "SDL.h"
#include "../Graphics/TextureManager.h"
#include "Player.h"
#include "../Inputs/Input.h"


Player::Player(Properties *props) : Character(props) {
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 10, 80);
    m_RigidBody = new RigidBody();
}

void Player::Draw() {
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Player::Update(float dt) {
    m_Animation->SetProps("player_idle", 1, 10, 80);
    m_RigidBody->UnsetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        m_Animation->SetProps("player_run", 1, 8, 80, SDL_FLIP_HORIZONTAL);
        m_RigidBody->ApplyForceX(5 * BACKWARD);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        m_Animation->SetProps("player_run", 1, 8, 80, SDL_FLIP_NONE);
        m_RigidBody->ApplyForceX(5 * FORWARD);
    }

    m_Animation->Update();
    m_RigidBody->Update(0.5);
    m_Transform->TranslateX(m_RigidBody->GetPosition().X);
}

void Player::Clean() {
    TextureManager::GetInstance()->Clean();
}