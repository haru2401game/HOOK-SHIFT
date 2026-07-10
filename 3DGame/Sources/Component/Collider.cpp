#include "pch.h"
#include "Collider.h"

#include <algorithm>

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

bool Collider::Raycast(
    const Vector3& origin,
    const Vector3& direction,
    float maxDistance,
    float& hitDistance) const
{
    Vector3 min = m_center - m_size * 0.5f;
    Vector3 max = m_center + m_size * 0.5f;

    float tMin = 0.0f;
    float tMax = maxDistance;

    const float* o = &origin.x;
    const float* d = &direction.x;
    const float* minV = &min.x;
    const float* maxV = &max.x;

    for (int i = 0; i < 3; i++)
    {
        if (fabs(d[i]) < 0.00001f)
        {
            if (o[i] < minV[i] || o[i] > maxV[i])
                return false;
        }
        else
        {
            float inv = 1.0f / d[i];

            float t1 = (minV[i] - o[i]) * inv;
            float t2 = (maxV[i] - o[i]) * inv;

            if (t1 > t2)
                std::swap(t1, t2);

            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);

            if (tMin > tMax)
                return false;
        }
    }

    hitDistance = tMin;
    return true;
}