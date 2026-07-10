#include "pch.h"
#include "Collider.h"

#include "Sources/Object/GameObject.h"

using namespace DirectX::SimpleMath;

void Collider::SetCenter(const Vector3& center)
{
    m_center = center;
}

void Collider::SetSize(const Vector3& size)
{
    m_size = size;
}

const Vector3& Collider::GetCenter() const
{
    return m_center;
}

const Vector3& Collider::GetSize() const
{
    return m_size;
}

bool Collider::Intersects(const Collider& other) const
{
    Vector3 halfSize = m_size * 0.5f;
    Vector3 otherHalfSize = other.m_size * 0.5f;

    return
        fabs(m_center.x - other.m_center.x) <= (halfSize.x + otherHalfSize.x) &&
        fabs(m_center.y - other.m_center.y) <= (halfSize.y + otherHalfSize.y) &&
        fabs(m_center.z - other.m_center.z) <= (halfSize.z + otherHalfSize.z);
}

void Collider::SetOwner(GameObject* owner)
{
    m_owner = owner;
}