#pragma once

#include <SimpleMath.h>

class GameObject;

class Collider
{
public:
    Collider() = default;

    void SetCenter(const DirectX::SimpleMath::Vector3& center);
    void SetSize(const DirectX::SimpleMath::Vector3& size);

    const DirectX::SimpleMath::Vector3& GetCenter() const;
    const DirectX::SimpleMath::Vector3& GetSize() const;

    bool Intersects(const Collider& other) const;

    void SetOwner(GameObject* owner);

    GameObject* GetOwner() const { return m_owner; };

    bool Raycast(
        const DirectX::SimpleMath::Vector3& origin,
        const DirectX::SimpleMath::Vector3& direction,
        float maxDistance,
        float& hitDistance) const;

private:
    DirectX::SimpleMath::Vector3 m_center = {};
    DirectX::SimpleMath::Vector3 m_size = { 1.0f,1.0f,1.0f };
    GameObject* m_owner = nullptr;
};