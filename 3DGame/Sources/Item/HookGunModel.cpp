#include "pch.h"
#include "HookGunModel.h"
using namespace DirectX::SimpleMath;

using namespace DirectX;

void HookGunModel::Initialize(
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

    D3D11_DEPTH_STENCIL_DESC desc{};
    desc.DepthEnable = false;
    desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    desc.StencilEnable = false;

    device->CreateDepthStencilState(
        &desc,
        m_noDepthState.ReleaseAndGetAddressOf());
}

void HookGunModel::Update(float)
{
}

void HookGunModel::UpdateTransform()
{
    m_world =
        Matrix::CreateTranslation(
            5.0f,
            -5.0f,
            -2.0f);
}

void HookGunModel::Render(
    const Matrix& projection)
{
    Matrix view = Matrix::Identity;

    Matrix gun =
        m_world
        *
        Matrix::CreateScale(
            0.3f,
            0.3f,
            1.2f);


    m_cube->Draw(
        gun,
        view,
        projection,
        Colors::DarkGray);
}