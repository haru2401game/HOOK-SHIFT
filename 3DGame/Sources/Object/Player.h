#include <GeometricPrimitive.h>
#include <CommonStates.h>
#include "GameObject.h"
#include "Sources/Item/HookGun.h"
#include "Sources/Item/HookGunModel.h"

class Player : public GameObject
{
public:
    void Initialize(
        DX::DeviceResources* deviceResources) override;

    void Update(float deltaTime) override;

    void Render(
        const Matrix& view,
        const Matrix& projection) override;

    Vector3 GetMoveDirection() const;
    Vector3 GetNextPosition(float deltaTime) const override;

    void MoveTo(const Vector3& position) override;

    void OnGroundCollision(float y) override;

    void Jump();

    float GetYaw() const { return m_yaw; }
    float GetPitch() const{ return m_pitch; }
    Vector3 GetForward() const;
    Vector3 GetRight() const;
    Vector3 GetUp() const;
    Vector3 GetEyePosition() const;

    Vector3 GetHookPoint() const;

    // ----- フックガン関連 ----- //

    void ShootHook();
    void ReleaseHook();
    void RenderViewModel(const Matrix& projection);
    Vector3 GetWorldMuzzlePosition() const;

    HookGun& GetHookGun() { return m_hookGun; }
    const HookGun& GetHookGun() const { return m_hookGun; }
    HookGunModel& GetHookGunModel() { return m_hookGunModel; }
    const HookGunModel& GetHookGunModel() const { return m_hookGunModel; }

private:

    void UpdateRotation(float deltaTime);

private:
    std::unique_ptr<DirectX::GeometricPrimitive> m_cube;
    std::unique_ptr<DirectX::CommonStates> m_states;

    float m_pitch = 0.0f;
    float m_yaw = 0.0f;

    float m_moveSpeed = 8.0f;
    float m_runSpeed = 14.0f;

    HookGun m_hookGun;
    HookGunModel m_hookGunModel;

private:
    constexpr static float JUMP_POWER = 8.0f;

    static constexpr float LOOK_SENSITIVITY = 0.002f;

    static constexpr float RUN_SPEED = 10.0f;

    static constexpr float HOOK_RELEASE_POWER = 10.0f;

    static constexpr float EYE_HEIGHT = 0.0f;

    static constexpr float HOOK_OFFSET_RIGHT = 0.35f;
    static constexpr float HOOK_OFFSET_DOWN = 0.25f;
    static constexpr float HOOK_OFFSET_FORWARD = 0.5f;
};