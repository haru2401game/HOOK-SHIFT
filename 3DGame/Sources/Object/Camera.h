#pragma once

#include "Player.h"

class Camera
{
public:
    void Update(float deltaTime);

    DirectX::SimpleMath::Matrix GetView() const;
    DirectX::SimpleMath::Matrix GetProjection() const;

    void SetPlayer(const Player* player);
    void SetAspectRatio(float aspectRatio);

    void SetFixedCamera(
        const DirectX::SimpleMath::Vector3& position,
        const DirectX::SimpleMath::Vector3& target);

private:
    const Player* m_player = nullptr;

    float m_aspectRatio = 16.0f / 9.0f;

    // 固定カメラ用
    bool m_isFixed = false;

    DirectX::SimpleMath::Vector3 m_position = { 0,0,0 };
    DirectX::SimpleMath::Vector3 m_target = { 0,0,1 };

private:
    // カメラ設定
    static constexpr float FOV = DirectX::XMConvertToRadians(60.0f);
    static constexpr float NEAR_CLIP = 0.1f;
    static constexpr float FAR_CLIP = 10000.0f;
};