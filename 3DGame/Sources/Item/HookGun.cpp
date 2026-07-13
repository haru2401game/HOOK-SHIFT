#include "pch.h"
#include "HookGun.h"

void HookGun::Initialize(DX::DeviceResources* deviceResources)
{
    auto context =
        deviceResources->GetD3DDeviceContext();

    m_wire =
        DirectX::GeometricPrimitive::CreateCube(context);
}

void HookGun::Update(float deltaTime)
{
    m_stateTimer += deltaTime;
}

void HookGun::Hook(const Vector3& point)
{
    m_hookPoint = point;
    m_state = HookState::Hooked;
    m_stateTimer = 0.0f;
}

void HookGun::Release()
{
    m_state = HookState::Idle;
    m_stateTimer = 0.0f;
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

float HookGun::GetStateTimer() const
{
    return m_stateTimer;
}

void HookGun::StartShoot()
{
    if (m_state != HookState::Idle)
        return;

    m_state = HookState::Shooting;
    m_stateTimer = 0.0f;
}

void HookGun::StartPull()
{
    if (m_state == HookState::Hooked)
    {
        m_state = HookState::Pulling;
    }
}

Vector3 HookGun::GetHookDirection(
    const Vector3& playerPosition) const
{
    Vector3 direction =
        m_hookPoint - playerPosition;

    direction.Normalize();

    return direction;
}