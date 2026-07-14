#pragma once

#include <SimpleMath.h>

#include "Sources/Component/Collider.h"
#include "Sources/Component/RigidBody.h"

using namespace DirectX::SimpleMath;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject() = default;

    virtual void Initialize(
        DX::DeviceResources* deviceResources) = 0;

    virtual void Update(
        float deltaTime) = 0;

    virtual void Render(
        const Matrix& view,
        const Matrix& projection) = 0;

    const Vector3& GetPosition() const
    {
        return m_position;
    }

    const Vector3& GetRotation() const
    {
        return m_rotation;
    }

    const Vector3& GetScale() const
    {
        return m_scale;
    }

    const Vector3& GetColor() const
    {
        return m_color;
    }

    Collider& GetCollider()
    {
        return m_collider;
    }

    const Collider& GetCollider() const
    {
        return m_collider;
    }

    RigidBody& GetRigidBody() 
    {
        return m_rigidBody;
    }

    const RigidBody& GetRigidBody() const
    {
        return m_rigidBody;
    }

    virtual Vector3 GetNextPosition(float deltaTime) const
    {
        return m_position;
    }

    virtual void MoveTo(const Vector3& position)
    {
        SetPosition(position);
    }

    virtual void OnGroundCollision(float y)
    {
    }

public:

    void SetPosition(
        const Vector3& position);

    void SetRotation(
        const Vector3& rotation);

    void SetScale(
        const Vector3& scale);

    void SetColor(
        const Vector3& color);

    void UpdateCollider();

protected:

    DX::DeviceResources* m_deviceResources = nullptr;

    Vector3 m_position = Vector3::Zero;

    Vector3 m_rotation = Vector3::Zero;

    Vector3 m_scale = Vector3::One;

    Vector3 m_color = Vector3::One;

    Collider m_collider;
    RigidBody m_rigidBody;
};