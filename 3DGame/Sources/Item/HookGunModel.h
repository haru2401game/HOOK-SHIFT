#pragma once

#include <memory>

#include <SimpleMath.h>
#include <GeometricPrimitive.h>
#include <CommonStates.h>
#include <DeviceResources.h>

class HookGunModel
{
public:

    void Initialize(
        DX::DeviceResources* deviceResources);

    void Update(
        float deltaTime);

    void UpdateTransform();

    void Render(
        const DirectX::SimpleMath::Matrix& projection);

private:

    DX::DeviceResources* m_deviceResources = nullptr;

    std::unique_ptr<DirectX::GeometricPrimitive> m_cube;

    std::unique_ptr<DirectX::CommonStates> m_states;

    DirectX::SimpleMath::Matrix m_world =
        DirectX::SimpleMath::Matrix::Identity;

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_noDepthState;
};