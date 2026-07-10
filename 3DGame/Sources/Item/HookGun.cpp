#include "pch.h"
#include "HookGun.h"

void HookGun::Hook(const Vector3& point)
{
    m_hookPoint = point;
    m_state = HookState::Hooked;
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
    return m_state == HookState::Hooked;
}

const Vector3& HookGun::GetHookPoint() const
{
    return m_hookPoint;
}

void HookGun::StartShoot()
{
    if (m_state != HookState::Idle)
        return;

    m_state = HookState::Shooting;
}