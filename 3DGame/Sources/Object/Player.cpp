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
}

void Player::Update(float deltaTime)
{
    UpdateRotation(deltaTime);

    if (Input::GetKeyDown(VK_SPACE))
    {
        Jump();
    }
}

void Player::Render(
    const Matrix& view,
    const Matrix& projection)
{
    Matrix world =
        Matrix::CreateScale(GetScale()) *
        Matrix::CreateTranslation(GetPosition());

    m_cube->Draw(
        world,
        view,
        projection,
        DirectX::Colors::Blue);
}

void Player::UpdateRotation(float deltaTime)
{
    (void)deltaTime;

    constexpr float sensitivity = 0.002f;

    m_yaw -= Input::GetMouseDeltaX() * sensitivity;
}

Vector3 Player::GetNextPosition(float deltaTime) const
{
    Vector3 forward(sinf(m_yaw), 0.0f, cosf(m_yaw));
    Vector3 right(cosf(m_yaw), 0.0f, -sinf(m_yaw));

    Vector3 move = Vector3::Zero;

    if (Input::GetKey('W')) move += forward;
    if (Input::GetKey('S')) move -= forward;
    if (Input::GetKey('A')) move += right;
    if (Input::GetKey('D')) move -= right;

    if (move.LengthSquared() > 0.0f)
    {
        move.Normalize();
    }
    return m_position + move * m_moveSpeed * deltaTime;
}

void Player::MoveTo(const Vector3& position)
{
    SetPosition(position);
}

void Player::OnGroundCollision(float y)
{
    // 必要になったら着地エフェクトやSEをここに書く
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