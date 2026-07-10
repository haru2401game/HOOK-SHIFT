#pragma once

#include <vector>
#include "Sources/Component/Collider.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

class GameObject;

class ColliderManager
{
public:

    void Register(const Collider* collider);

    bool CheckCollision(
        const Collider& collider) const;

    bool Raycast(
        const Vector3& origin,
        const Vector3& direction,
        float maxDistance,
        const GameObject* owner,
        const Collider*& hitCollider,
        Vector3& hitPoint) const;
private:

    std::vector<const Collider*> m_colliders;
};