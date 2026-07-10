#include "pch.h"
#include "PhysicsManager.h"

#include "Sources/Object/ObjectManager.h"
#include "Sources/Component/ColliderManager.h"

using namespace DirectX::SimpleMath;

namespace
{
    constexpr float GRAVITY = -20.0f;
}

void PhysicsManager::Update(
    ObjectManager& objectManager,
    ColliderManager& colliderManager,
    float deltaTime)
{
    for (auto& obj : objectManager.GetObjects())
    {
        GameObject* object = obj.get();
        RigidBody& body = object->GetRigidBody();

        // 重力
        if (body.UseGravity())
        {
            body.AddVelocity(
                Vector3(0.0f, GRAVITY * deltaTime, 0.0f));
        }

        Vector3 current = object->GetPosition();

        // オブジェクト固有の移動（Playerなら入力）
        Vector3 next = object->GetNextPosition(deltaTime);

        // Rigidbodyの速度による移動
        next += body.GetVelocity() * deltaTime;

        Collider col = object->GetCollider();

        //=========================
        // X
        //=========================
        Vector3 test = current;
        test.x = next.x;

        col.SetCenter(test);

        if (!colliderManager.CheckCollision(col))
        {
            current.x = next.x;
        }

        //=========================
        // Z
        //=========================
        test = current;
        test.z = next.z;

        col.SetCenter(test);

        if (!colliderManager.CheckCollision(col))
        {
            current.z = next.z;
        }

        //=========================
        // Y
        //=========================
        test = current;
        test.y = next.y;

        col.SetCenter(test);

        if (!colliderManager.CheckCollision(col))
        {
            current.y = next.y;
            body.SetGround(false);
        }
        else
        {
            // 着地
            Vector3 velocity = body.GetVelocity();
            velocity.y = 0.0f;
            body.SetVelocity(velocity);

            body.SetGround(true);

            object->OnGroundCollision(current.y);
        }

        object->MoveTo(current);
    }
}