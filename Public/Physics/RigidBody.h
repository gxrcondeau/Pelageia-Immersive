//
// Created by pylinskyi.k on 02/11/2023.
//

#ifndef PELAGEIA_IMMERSIVE_RIGIDBODY_H
#define PELAGEIA_IMMERSIVE_RIGIDBODY_H

#include "Vector2D.h"

#define UNI_MASS 1.0f

class RigidBody
{
public:
    RigidBody() : m_Mass(UNI_MASS) {}

    inline void ApplyForce(Vector2D F) { m_Force = F; }
    inline void ApplyForce(float Fx, float Fy) { m_Force.X = Fx; m_Force.Y = Fy; }
    inline void ApplyForceX(float Fx) { m_Force.X = Fx; }
    inline void ApplyForceY(float Fy) { m_Force.Y = Fy; }
    inline void UnsetForce() { m_Force = Vector2D(0, 0); }

    inline void ApplyFriction(Vector2D Fr) { m_Friction = Fr; }
    inline void ApplyFriction(float FrX, float FrY) { m_Friction.X = FrX; m_Friction.Y = FrY; }
    inline void UnsetFriction() { m_Friction = Vector2D(0, 0); }

    inline void ApplyMass(float mass) { m_Mass = mass; }
    inline void UnsetMass() { m_Mass = 0; }

    void Update(float deltaTime)
    {
        CalculateAcceleration();
        UpdateVelocity(deltaTime);
    }

private:
    Vector2D m_Force;
    Vector2D m_Friction;
    float m_Mass;

    Vector2D m_Velocity;
    Vector2D m_Acceleration;

    void CalculateAcceleration()
    {
        m_Acceleration.X = (m_Force.X - m_Friction.X) / m_Mass;
        m_Acceleration.Y = (m_Force.Y - m_Friction.Y) / m_Mass;
    }

    void UpdateVelocity(float deltaTime)
    {
        m_Velocity += m_Acceleration * deltaTime;
    }
};

#endif  // PELAGEIA_IMMERSIVE_RIGIDBODY_H
