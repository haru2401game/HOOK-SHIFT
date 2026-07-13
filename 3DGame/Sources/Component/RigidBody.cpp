#include "pch.h"
#include "RigidBody.h"

void RigidBody::SetVelocity(const Vector3& velocity)
{
    m_velocity = velocity;
}

const Vector3& RigidBody::GetVelocity() const
{
    return m_velocity;
}

void RigidBody::AddVelocity(const Vector3& velocity)
{
    m_velocity += velocity;
}

void RigidBody::SetGround(bool ground)
{
    m_isGround = ground;
}

bool RigidBody::IsGround() const
{
    return m_isGround;
}

void RigidBody::SetStatic(bool isStatic)
{
    m_isStatic = isStatic;

    if (m_isStatic)
    {
        m_velocity = Vector3::Zero;
    }
}

bool RigidBody::IsStatic() const
{
    return m_isStatic;
}

void RigidBody::SetUseGravity(bool useGravity)
{
    m_useGravity = useGravity;
}

bool RigidBody::UseGravity() const
{
    return m_useGravity;
}

void RigidBody::ApplyDrag(float deltaTime)
{
    float drag;

    if (m_isGround)
    {
        drag = 8.0f;   // 地面は強め
    }
    else
    {
        drag = 1.5f;   // 空中は弱め
    }

    float rate = 1.0f - drag * deltaTime;

    m_velocity.x *= rate;
    m_velocity.z *= rate;
}