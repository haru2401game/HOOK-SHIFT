#include "pch.h"
#include "PhysicsManager.h"

#include "Sources/Object/ObjectManager.h"
#include "Sources/Component/ColliderManager.h"
#include "Sources/Object/GameObject.h"
#include "Sources/Component/RigidBody.h"

using namespace DirectX::SimpleMath;

void PhysicsManager::Update(
    ObjectManager& objectManager,
    ColliderManager& colliderManager,
    float deltaTime)
{
    for (auto& obj : objectManager.GetObjects())
    {
        GameObject* object = obj.get();

        RigidBody& body =
            object->GetRigidBody();

        if (body.IsStatic())
        {
            continue;
        }

        UpdateGravity(
            body,
            deltaTime);

        UpdateMovement(
            object,
            colliderManager,
            deltaTime);
    }
}

void PhysicsManager::UpdateGravity(
    RigidBody& body,
    float deltaTime)
{
    if (!body.UseGravity())
    {
        return;
    }

    body.AddVelocity(
        Vector3(
            0.0f,
            GRAVITY_POWER * deltaTime,
            0.0f));

    body.ApplyDrag(deltaTime);
}

void PhysicsManager::UpdateMovement(
    GameObject* object,
    ColliderManager& colliderManager,
    float deltaTime)
{
    Vector3 current =
        object->GetPosition();

    Vector3 next =
        object->GetNextPosition(deltaTime);

    next +=
        object->GetRigidBody()
        .GetVelocity()
        * deltaTime;


    MoveX(
        object,
        colliderManager,
        current,
        next);

    MoveZ(
        object,
        colliderManager,
        current,
        next);

    MoveY(
        object,
        colliderManager,
        current,
        next);

    object->MoveTo(current);
}

void PhysicsManager::MoveX(
    GameObject* object,
    ColliderManager& colliderManager,
    Vector3& current,
    const Vector3& next)
{
    Collider col =
        object->GetCollider();

    Vector3 test = current;

    test.x = next.x;

    col.SetCenter(test);


    if (!colliderManager.CheckCollision(col))
    {
        current.x = next.x;
    }
}

void PhysicsManager::MoveZ(
    GameObject* object,
    ColliderManager& colliderManager,
    Vector3& current,
    const Vector3& next)
{
    Collider col =
        object->GetCollider();

    Vector3 test = current;

    test.z = next.z;

    col.SetCenter(test);

    if (!colliderManager.CheckCollision(col))
    {
        current.z = next.z;
    }
}

void PhysicsManager::MoveY(
    GameObject* object,
    ColliderManager& colliderManager,
    Vector3& current,
    const Vector3& next)
{
    Collider col =
        object->GetCollider();

    Vector3 test = current;

    test.y = next.y;

    col.SetCenter(test);

    RigidBody& body =
        object->GetRigidBody();

    if (!colliderManager.CheckCollision(col))
    {
        current.y = next.y;

        body.SetGround(false);
    }
    else
    {
        bool wasGround =
            body.IsGround();

        Vector3 velocity =
            body.GetVelocity();

        velocity.y = 0.0f;

        body.SetVelocity(velocity);

        body.SetGround(true);

        if (!wasGround)
        {
            object->OnGroundCollision(current.y);
        }
    }
}