#include "pch.h"
#include "HookGun.h"

void HookGun::StartShoot()
{
    if (m_state != HookState::Idle)
        return;

    m_state = HookState::Shooting;
}

void HookGun::Hook(
    const Vector3& point)
{
    m_hookPoint = point;

    m_state = HookState::Hooked;
}

void HookGun::StartPull()
{
    if (m_state == HookState::Hooked)
    {
        m_state = HookState::Pulling;
    }
}

void HookGun::Release()
{
    m_state = HookState::Idle;
}

HookState HookGun::GetState() const
{
    return m_state;
}

bool HookGun::IsHooked() const
{
    return
        m_state == HookState::Hooked ||
        m_state == HookState::Pulling;
}

const Vector3& HookGun::GetHookPoint() const
{
    return m_hookPoint;
}

Vector3 HookGun::GetHookDirection(
    const Vector3& playerPosition) const
{
    Vector3 direction = m_hookPoint - playerPosition;

    direction.Normalize();

    return direction;
}