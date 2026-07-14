#pragma once

#include <SimpleMath.h>

using namespace DirectX::SimpleMath;


enum class HookState
{
    Idle,
    Shooting,
    Hooked,
    Pulling
};


class HookGun
{
public:

    void StartShoot();

    void Hook(
        const Vector3& point);

    void StartPull();

    void Release();


    HookState GetState() const;

    bool IsHooked() const;


    const Vector3& GetHookPoint() const;

    Vector3 GetHookDirection(
        const Vector3& playerPosition) const;


private:

    HookState m_state =
        HookState::Idle;

    Vector3 m_hookPoint =
        Vector3::Zero;
};