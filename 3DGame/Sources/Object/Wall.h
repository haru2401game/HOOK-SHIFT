#pragma once

#include <memory>

#include <GeometricPrimitive.h>
#include <CommonStates.h>
#include "DeviceResources.h"

#include "Sources/Object/GameObject.h"

class Wall : public GameObject
{
public:
    Wall(
        const Vector3& position,
        const Vector3& scale);

    void Initialize(
        DX::DeviceResources* deviceResources) override;

    void Update(float deltaTime) override;

    void Render(
        const DirectX::SimpleMath::Matrix& view,
        const DirectX::SimpleMath::Matrix& projection) override;

private:
    std::unique_ptr<DirectX::GeometricPrimitive> m_cube;
    std::unique_ptr<DirectX::CommonStates> m_states;
};