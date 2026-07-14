#include "pch.h"
#include "Camera.h"

using namespace DirectX::SimpleMath;

void Camera::Update(float deltaTime)
{
    //更新処理
}

Matrix Camera::GetView() const
{
    if (!m_player)
    {
        return Matrix::Identity;
    }

    Vector3 position = m_player->GetEyePosition();
    Vector3 target = position + m_player->GetForward();

    return Matrix::CreateLookAt(
        position,
        target,
        Vector3::Up
    );
}

Matrix Camera::GetProjection() const
{
    return Matrix::CreatePerspectiveFieldOfView(
        FOV,
        m_aspectRatio,
        NEAR_CLIP,
        FAR_CLIP
    );
}

void Camera::SetPlayer(const Player* player)
{
    m_player = player;
}

void Camera::SetAspectRatio(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
}