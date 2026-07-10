#include "pch.h"
#include "ColliderManager.h"


void ColliderManager::Register(
    const Collider* collider)
{
    m_colliders.push_back(collider);
}


bool ColliderManager::CheckCollision(
    const Collider& collider) const
{
    for (auto other : m_colliders)
    {
        if (other == &collider)
            continue;

        // 自分自身を無視
        if (other->GetOwner() == collider.GetOwner())
            continue;

        if (collider.Intersects(*other))
            return true;
    }
    return false;
}

bool ColliderManager::Raycast(
    const Vector3& origin,
    const Vector3& direction,
    float maxDistance,
    const GameObject* owner,
    const Collider*& hitCollider,
    Vector3& hitPoint) const
{
    float nearest = maxDistance;
    hitCollider = nullptr;

    for (auto collider : m_colliders)
    {
        if (!collider->GetOwner())
            continue;

        if (collider->GetOwner() == owner)
            continue;

        float distance;

        if (collider->Raycast(origin, direction, maxDistance, distance))
        {
            if (distance < nearest)
            {
                nearest = distance;
                hitCollider = collider;
            }
        }
    }

    if (hitCollider)
    {
        hitPoint = origin + direction * nearest;
        return true;
    }

    return false;
}