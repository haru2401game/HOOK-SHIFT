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
    void UpdateRotation(float deltaTime);
    DirectX::SimpleMath::Vector3 GetForward() const;

private:
    const Player* m_player = nullptr;

    DirectX::SimpleMath::Vector3 m_position = {};

    float m_aspectRatio = 16.0f / 9.0f;


    // カメラ設定
    static constexpr float FOV =
        DirectX::XMConvertToRadians(60.0f);

    static constexpr float NEAR_CLIP = 0.1f;

    static constexpr float FAR_CLIP = 1000.0f;


    // マウス感度
    static constexpr float MOUSE_SENSITIVITY = 0.002f;


    // 上下回転制限
    static constexpr float MIN_PITCH =
        DirectX::XMConvertToRadians(-89.0f);

    static constexpr float MAX_PITCH =
        DirectX::XMConvertToRadians(89.0f);
};