#include <GeometricPrimitive.h>
#include <CommonStates.h>
#include "GameObject.h"

class Player : public GameObject
{
public:
    void Initialize(
        DX::DeviceResources* deviceResources) override;

    void Update(float deltaTime) override;

    void Render(
        const Matrix& view,
        const Matrix& projection) override;

    Vector3 GetNextPosition(float deltaTime) const override;

    void MoveTo(const Vector3& position) override;

    void OnGroundCollision(float y) override;

    void Jump();

    void Land(
        float groundY);

    float GetYaw() const { return m_yaw; }

private:

    void UpdateRotation(float deltaTime);

private:
    constexpr static float JUMP_POWER = 8.0f;

    std::unique_ptr<DirectX::GeometricPrimitive> m_cube;
    std::unique_ptr<DirectX::CommonStates> m_states;

    float m_yaw = 0.0f;

    float m_moveSpeed = 5.0f;
};