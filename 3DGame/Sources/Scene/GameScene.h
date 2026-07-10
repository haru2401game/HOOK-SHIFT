#pragma once

#include "Sources/Scene/Scene.h"

#include "Sources/Object/Camera.h"
#include "Sources/Object/ObjectManager.h"
#include "Sources/Component/ColliderManager.h"
#include <Sources/Physics/PhysicsManager.h>

class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() = default;

    void Initialize() override;
    void Finalize() override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    void CreateCamera();
    // ステージロード機能実装後移動予定
    void CreateObjects();
    void CreateObjectManager();
    void CreateColliderManager();
    void CreatePhysicsManager();

private:
    std::unique_ptr<ObjectManager> m_objectManager;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<ColliderManager> m_colliderManager;
    std::unique_ptr<PhysicsManager> m_physicsManager;
};