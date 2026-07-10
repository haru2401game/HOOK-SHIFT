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

void RigidBody::SetUseGravity(bool useGravity)
{
    m_useGravity = useGravity;
}

bool RigidBody::UseGravity() const
{
    return m_useGravity;
}