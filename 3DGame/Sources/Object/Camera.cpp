#include "pch.h"
#include "Camera.h"
#include "Sources/Input.h"

using namespace DirectX::SimpleMath;

void Camera::Update(float deltaTime)
{
    UpdateRotation(deltaTime);
}

Matrix Camera::GetView() const
{
    if (!m_player)
    {
        return Matrix::Identity;
    }

    Vector3 position = m_player->GetPosition();
    Vector3 target = position + GetForward();

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

void Camera::UpdateRotation(float deltaTime)
{
    float pitch = m_player->GetPitch();

    pitch -= Input::GetMouseDeltaY() * MOUSE_SENSITIVITY;

    pitch = std::clamp(
        pitch,
        MIN_PITCH,
        MAX_PITCH);
}

Vector3 Camera::GetForward() const
{
    float yaw = m_player->GetYaw();
    float pitch = m_player->GetPitch();
    Vector3 forward;

    forward.x = cosf(pitch) * sinf(yaw);
    forward.y = sinf(pitch);
    forward.z = cosf(pitch) * cosf(yaw);

    return forward;
}