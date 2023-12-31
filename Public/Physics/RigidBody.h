//
// Created by pylinskyi.k on 02/11/2023.
//

#ifndef PELAGEIA_IMMERSIVE_RIGIDBODY_H
#define PELAGEIA_IMMERSIVE_RIGIDBODY_H

#include "Vector2D.h"

#define UNI_MASS 1.0f
#define GRAVITY 6.5f

class RigidBody
{
public:
    RigidBody() {}
    virtual ~RigidBody() {}

    inline Vector2D GetPosition() const { return m_Position; }

    inline void SetMass(float mass) { m_Mass = mass; }
    inline void SetGravity(float gravity) { m_Gravity = gravity; }

    inline void ApplyForce(Vector2D F) { m_Force = F; }
    inline void ApplyForceX(float Fx) { m_Force.X = Fx; }
    inline void ApplyForceY(float Fy) { m_Force.Y = Fy; }
    inline void UnsetForce() { m_Force = Vector2D(0, 0); }

    inline void ApplyFriction(Vector2D Fr) { m_Friction = Fr; }
    inline void ApplyFriction() { m_Friction = Vector2D(0, 0); }

    void Update(float dt)
    {
        m_Acceleration.X = (m_Force.X + m_Friction.X) / m_Mass;
        m_Acceleration.Y = m_Gravity + m_Force.Y / m_Mass;
        m_Velocity = m_Acceleration * dt;
        m_Position = m_Velocity * dt;
    }

private:
    float m_Mass = UNI_MASS;
    float m_Gravity = GRAVITY;

    Vector2D m_Force;
    Vector2D m_Friction;

    Vector2D m_Position;
    Vector2D m_Velocity;
    Vector2D m_Acceleration;
};

#endif  // PELAGEIA_IMMERSIVE_RIGIDBODY_H
