#pragma once

#include <vector>

#include "Sources/Component/Collider.h"

class ColliderManager
{
public:

    void Register(const Collider* collider);

    bool CheckCollision(
        const Collider& collider) const;

private:

    std::vector<const Collider*> m_colliders;
};