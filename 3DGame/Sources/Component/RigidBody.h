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

    void SetStatic(bool isStatic);
    bool IsStatic() const;

    void SetUseGravity(bool useGravity);
    bool UseGravity() const;

    void ApplyDrag(float deltaTime);

private:
    Vector3 m_velocity = Vector3::Zero;

    bool m_isGround = false;
    bool m_useGravity = true;
    bool m_isStatic = false;
};