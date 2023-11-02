//
// Created by admin on 24/10/2023.
//

#include "SDL.h"
#include "../Graphics/TextureManager.h"
#include "Player.h"


Player::Player(Properties *props) : Character(props) {
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 10, 80, SDL_FLIP_HORIZONTAL);
    m_RigidBody = new RigidBody();
}

void Player::Draw() {
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Player::Update(float dt) {
    m_Animation->Update();
    m_RigidBody->Update(0.2);
    m_RigidBody->ApplyForceX(5);
    m_Transform->Translate(m_RigidBody->GetPosition());
}

void Player::Clean() {
    TextureManager::GetInstance()->Clean();
}