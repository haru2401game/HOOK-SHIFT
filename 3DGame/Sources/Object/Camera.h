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

private:
    const Player* m_player = nullptr;

    float m_aspectRatio = 16.0f / 9.0f;

private:
    // カメラ設定
    static constexpr float FOV = DirectX::XMConvertToRadians(60.0f);
    static constexpr float NEAR_CLIP = 0.1f;
    static constexpr float FAR_CLIP = 1000.0f;
};