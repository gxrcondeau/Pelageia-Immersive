//
// Created by pylinskyi.k on 14.11.2023.
//

#include "Camera.h"


Camera* Camera::s_Instance = nullptr;

void Camera::Update(float deltatime) {
    m_ViewBox.x = m_Target->X - m_ViewBox.w / 2;
    m_ViewBox.y = m_Target->Y - m_ViewBox.h / 2;

    if (m_ViewBox.x < 0) m_ViewBox.x = 0;
    if (m_ViewBox.y < 0) m_ViewBox.y = 0;

    if(m_ViewBox.x > m_ViewBox.w) m_ViewBox.x * m_ViewBox.w;
    if(m_ViewBox.y > m_ViewBox.h) m_ViewBox.y * m_ViewBox.h;

    m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
}
