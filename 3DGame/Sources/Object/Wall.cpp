#include "pch.h"
#include "Wall.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Wall::Wall(
    const Vector3& position,
    const Vector3& scale)
{
    SetPosition(position);
    SetScale(scale);
}

void Wall::Initialize(
    DX::DeviceResources* deviceResources)
{
    m_deviceResources = deviceResources;

    auto device =
        deviceResources->GetD3DDevice();

    auto context =
        deviceResources->GetD3DDeviceContext();

    m_cube =
        GeometricPrimitive::CreateCube(context);

    m_states =
        std::make_unique<CommonStates>(device);
}

void Wall::Update(float deltaTime)
{
    // 現状は処理なし
    deltaTime;
}

void Wall::Render(
    const Matrix& view,
    const Matrix& projection)
{
    auto context = m_deviceResources->GetD3DDeviceContext();

    Matrix world =
        Matrix::CreateScale(GetScale()) *
        Matrix::CreateTranslation(GetPosition());

    Color color(
        GetColor().x,
        GetColor().y,
        GetColor().z,
        1.0f);

    m_cube->Draw(
        world,
        view,
        projection,
        color);
}