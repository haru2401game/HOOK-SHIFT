#include <SimpleMath.h>

class ColliderManager;
class ObjectManager;
class GameObject;
class RigidBody;

class PhysicsManager
{
public:
    void Update(
        ObjectManager& objectManager,
        ColliderManager& colliderManager,
        float deltaTime);

private:
    void UpdateGravity(
        RigidBody& body,
        float deltaTime);

    void UpdateMovement(
        GameObject* object,
        ColliderManager& colliderManager,
        float deltaTime);

    void MoveX(
        GameObject* object,
        ColliderManager& colliderManager,
        DirectX::SimpleMath::Vector3& current,
        const DirectX::SimpleMath::Vector3& next);

    void MoveZ(
        GameObject* object,
        ColliderManager& colliderManager,
        DirectX::SimpleMath::Vector3& current,
        const DirectX::SimpleMath::Vector3& next);

    void MoveY(
        GameObject* object,
        ColliderManager& colliderManager,
        DirectX::SimpleMath::Vector3& current,
        const DirectX::SimpleMath::Vector3& next);

private:
    static constexpr float GRAVITY_POWER = -20.0f;
};