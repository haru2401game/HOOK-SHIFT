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