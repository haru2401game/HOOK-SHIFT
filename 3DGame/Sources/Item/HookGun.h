#pragma once

#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

enum class HookState
{
    Idle,       // 待機
    Shooting,   // 発射中
    Hooked,     // 刺さった
    Pulling,    // 引っ張られ中
    Cooldown    // クールタイム
};

class HookGun
{
public:
    void Hook(const Vector3& point);
    void Release();

    HookState GetState() const;

    bool IsHooked() const;

    const Vector3& GetHookPoint() const;

    void StartShoot();

private:
    HookState m_state = HookState::Idle;
    Vector3 m_hookPoint = Vector3::Zero;
};