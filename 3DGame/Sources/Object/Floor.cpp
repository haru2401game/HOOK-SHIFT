#include "pch.h"
#include "Floor.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Floor::Floor(
    const Vector3& position,
    const Vector3& scale)
{
    SetPosition(position);
    SetScale(scale);
}

void Floor::Initialize(
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

void Floor::Update(float deltaTime)
{
    (void)deltaTime;
}

void Floor::Render(
    const Matrix& view,
    const Matrix& projection)
{
    auto context = m_deviceResources->GetD3DDeviceContext();

    context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
    context->RSSetState(m_states->CullCounterClockwise());

    Matrix world =
        Matrix::CreateScale(GetScale()) *
        Matrix::CreateTranslation(GetPosition());

    m_cube->Draw(world, view, projection);
}