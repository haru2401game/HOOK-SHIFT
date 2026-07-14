#include "pch.h"
#include "PhysicsManager.h"

#include "Sources/Object/ObjectManager.h"
#include "Sources/Component/ColliderManager.h"
#include <Sources/Object/Player.h>

using namespace DirectX::SimpleMath;

namespace
{
    // 重力
    constexpr float GRAVITY_POWER = -20.0f;

    // フック
    constexpr float HOOK_RANGE = 50.0f;
    constexpr float HOOK_PULL_POWER = 35.0f;
    constexpr float MAX_HOOK_PULL_SPEED = 60.0f;
    constexpr float HOOK_PULL_STOP_DISTANCE = 4.0f;
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

        if (body.IsStatic())
        {
            continue;
        }

        // 重力
        if (body.UseGravity())
        {
            body.AddVelocity(
                Vector3(0.0f, GRAVITY_POWER * deltaTime, 0.0f));
            // 摩擦減衰
            body.ApplyDrag(deltaTime);
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
            bool wasGround =
                body.IsGround();


            Vector3 velocity = body.GetVelocity();
            velocity.y = 0.0f;
            body.SetVelocity(velocity);


            body.SetGround(true);


            // 空中から着地した瞬間だけ
            if (!wasGround)
            {
                object->OnGroundCollision(current.y);
            }
        }

        object->MoveTo(current);

        Player* player = dynamic_cast<Player*>(object);

        if (!player)
        {
            continue;
        }

        HookGun& hook = player->GetHookGun();

        //===========================
        // 発射
        //===========================
        if (hook.GetState() == HookState::Shooting)
        {
            const Collider* hitCollider = nullptr;
            Vector3 hitPoint;

            if (colliderManager.Raycast(
                player->GetEyePosition(),
                player->GetForward(),
                HOOK_RANGE,
                player,
                hitCollider,
                hitPoint))
            {
                hook.Hook(hitPoint);     // Hookedになる
            }
            else
            {
                hook.Release();
            }
        }

        //===========================
        // 引っ張り開始
        //===========================
        if (hook.GetState() == HookState::Hooked)
        {
            hook.StartPull();

            Vector3 dir =
                hook.GetHookPoint() - player->GetPosition();

            dir.Normalize();

            Vector3 velocity = body.GetVelocity();

            // 最初だけ一気に加速
            velocity += dir * 15.0f;

            body.SetVelocity(velocity);
        }

        //===========================
        // 引っ張り中
        //===========================
        if (hook.GetState() == HookState::Pulling)
        {
            Vector3 dir =
                hook.GetHookPoint() - player->GetPosition();

            float distance = dir.Length();


            if (distance < HOOK_PULL_STOP_DISTANCE)
            {
                hook.Release();
            }
            else
            {
                dir.Normalize();

                Vector3 velocity =
                    body.GetVelocity();


                // フック方向への加速度
                velocity +=
                    dir * HOOK_PULL_POWER * deltaTime;


                // 最大速度制限
                float speed =
                    velocity.Length();

                if (speed > MAX_HOOK_PULL_SPEED)
                {
                    velocity.Normalize();
                    velocity *= MAX_HOOK_PULL_SPEED;
                }


                body.SetVelocity(velocity);
            }
        }
    }
}