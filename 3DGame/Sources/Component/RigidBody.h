#pragma once

#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

class RigidBody
{
public:
    void SetVelocity(const Vector3& velocity);
    const Vector3& GetVelocity() const;

    void AddVelocity(const Vector3& velocity);

    void SetGround(bool ground);
    bool IsGround() const;

    void SetUseGravity(bool useGravity);
    bool UseGravity() const;

private:
    Vector3 m_velocity = Vector3::Zero;

    bool m_isGround = false;
    bool m_useGravity = true;
};