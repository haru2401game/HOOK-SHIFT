#include "pch.h"
#include "Player.h"

void Player::Initialize(DX::DeviceResources* deviceResources)
{
    m_deviceResources = deviceResources;

    SetPosition({ 0.0f, 2.0f, -5.0f });
    SetScale({ 1.0f, 2.0f, 1.0f });

    auto device = deviceResources->GetD3DDevice();
    auto context = deviceResources->GetD3DDeviceContext();

    m_cube = DirectX::GeometricPrimitive::CreateCube(context);
    m_states = std::make_unique<DirectX::CommonStates>(device);

    // フックガンモデルの初期化処理
    m_hookGunModel.Initialize(deviceResources);
}

void Player::Update(float deltaTime)
{
    UpdateRotation(deltaTime);
    m_hookGunModel.UpdateTransform();

    if (Input::GetKeyDown(VK_SPACE))
    {
        ReleaseHook();
        Jump();
    }
    if (Input::GetKeyDown(VK_RBUTTON))
    {
        ShootHook();
    }
}

void Player::Render(
    const Matrix&,
    const Matrix&)
{
    // プレイヤー描画を入れてもいい
}

void Player::UpdateRotation(float deltaTime)
{
    m_pitch -= Input::GetMouseDeltaY() * LOOK_SENSITIVITY;
    m_yaw -= Input::GetMouseDeltaX() * LOOK_SENSITIVITY;

    constexpr float limit =
        DirectX::XM_PIDIV2 - 0.1f;

    m_pitch =
        std::clamp(
            m_pitch,
            -limit,
            limit);
}

Vector3 Player::GetMoveDirection() const
{
    Vector3 direction = Vector3::Zero;

    Vector3 forward = GetForward();
    forward.y = 0;
    forward.Normalize();

    Vector3 right = GetRight();

    if (Input::GetKey('W'))
        direction += forward;

    if (Input::GetKey('S'))
        direction -= forward;

    if (Input::GetKey('A'))
        direction += right;

    if (Input::GetKey('D'))
        direction -= right;

    if (direction.LengthSquared() > 0)
    {
        direction.Normalize();
    }

    return direction;
}

Vector3 Player::GetNextPosition(float deltaTime) const
{
    Vector3 next = GetPosition();

    float speed =
        Input::GetKey(VK_SHIFT)
        ? m_runSpeed
        : m_moveSpeed;

    next +=
        GetMoveDirection()
        * speed
        * deltaTime;

    next +=
        GetRigidBody().GetVelocity()
        * deltaTime;

    return next;
}

void Player::MoveTo(const Vector3& position)
{
    SetPosition(position);
}

void Player::OnGroundCollision(float y)
{
    // 着地処理
}

void Player::Jump()
{
    RigidBody& body = GetRigidBody();

    if (!body.IsGround())
        return;

    Vector3 velocity = body.GetVelocity();
    velocity.y = JUMP_POWER;

    body.SetVelocity(velocity);
    body.SetGround(false);
}

Vector3 Player::GetForward() const
{
    Vector3 forward;

    forward.x =
        cosf(m_pitch) * sinf(m_yaw);

    forward.y =
        sinf(m_pitch);

    forward.z =
        cosf(m_pitch) * cosf(m_yaw);

    forward.Normalize();

    return forward;
}

Vector3 Player::GetRight() const
{
    Vector3 right;

    right.x = cosf(m_yaw);
    right.y = 0.0f;
    right.z = -sinf(m_yaw);

    right.Normalize();

    return right;
}

Vector3 Player::GetUp() const
{
    Vector3 forward = GetForward();
    Vector3 right = GetRight();

    Vector3 up = forward.Cross(right);

    up.Normalize();

    return up;
}

Vector3 Player::GetEyePosition() const
{
    Vector3 eye = GetPosition();
    eye.y += EYE_HEIGHT;

    return eye;
}

Vector3 Player::GetHookPoint() const
{
    return m_hookGun.GetHookPoint();
}

void Player::ShootHook()
{
    m_hookGun.StartShoot();
}

void Player::ReleaseHook()
{
    if (m_hookGun.GetState() == HookState::Idle)
        return;

    Vector3 oldVelocity =
        GetRigidBody().GetVelocity();

    Vector3 hookVelocity =
        m_hookGun.GetHookDirection(
            GetPosition());

    m_hookGun.Release();

    oldVelocity +=
        hookVelocity * HOOK_RELEASE_POWER;

    GetRigidBody()
        .SetVelocity(oldVelocity);
}

void Player::RenderViewModel(
    const Matrix& projection)
{
    m_hookGunModel.Render(projection);
}

Vector3 Player::GetWorldMuzzlePosition() const
{
    Vector3 muzzle =
        GetEyePosition()
        + GetForward() * 0.8f
        - GetRight() * 0.35f
        - GetUp() * 0.35f;

    return muzzle;
}
