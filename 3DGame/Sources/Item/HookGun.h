#pragma once

#include <memory>

#include <SimpleMath.h>
#include <GeometricPrimitive.h>
#include <CommonStates.h>

using namespace DirectX::SimpleMath;

namespace DX
{
    class DeviceResources;
}

enum class HookState
{
    Idle,
    Shooting,
    Hooked,
    Pulling,
    Cooldown
};

class HookGun
{
public:
    void Initialize(DX::DeviceResources* deviceResources);

    void Update(float deltaTime);

    void StartShoot();

    void Hook(const Vector3& point);

    void StartPull();

    Vector3 GetHookDirection(const Vector3& playerPosition) const;

    void Release();

    HookState GetState() const;

    bool IsHooked() const;

    const Vector3& GetHookPoint() const;

    float GetStateTimer() const;

private:
    HookState m_state = HookState::Idle;

    Vector3 m_hookPoint = Vector3::Zero;

    float m_stateTimer = 0.0f;

    std::unique_ptr<DirectX::GeometricPrimitive> m_wire;
};