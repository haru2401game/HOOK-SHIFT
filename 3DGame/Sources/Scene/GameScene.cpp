#include "pch.h"
#include "GameScene.h"
#include <Sources/Object/Floor.h>
#include <Sources/Object/Wall.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

void GameScene::Initialize()
{
    Cursor::Hide();
    Cursor::LockToCenter();

    CreateColliderManager();
    CreateObjectManager();
    CreatePhysicsManager();
    CreateObjects();
    CreateCamera();
}

void GameScene::Finalize()
{
    Cursor::Unlock();
    Cursor::Show();
}

void GameScene::Update(float deltaTime)
{
    m_objectManager->Update(deltaTime);

    m_physicsManager->Update(
        *m_objectManager,
        *m_colliderManager,
        deltaTime);

    m_camera->Update(deltaTime);
}

void GameScene::Render()
{
    Matrix view = m_camera->GetView();
    Matrix proj = m_camera->GetProjection();

    m_objectManager->Render(
        view,
        proj);
}

void GameScene::CreateCamera()
{
    auto size = m_deviceResources->GetOutputSize();

    float aspect =
        static_cast<float>(size.right - size.left) /
        static_cast<float>(size.bottom - size.top);

    m_camera =
        std::make_unique<Camera>();

    Player* player =
        m_objectManager->GetObject<Player>();

    m_camera->SetPlayer(player);

    m_camera->SetAspectRatio(aspect);
}

void GameScene::CreateObjects()
{
    auto player =
        std::make_unique<Player>();

    m_objectManager->Add(
        std::move(player)
    );

    auto floor =
        std::make_unique<Floor>(
            Vector3(0, -0.5f, 0),
            Vector3(50, 1, 50)
        );

    m_objectManager->Add(
        std::move(floor)
    );

    auto wall =
        std::make_unique<Wall>(
            Vector3(0, 0.5f, 10),
            Vector3(10, 2, 1)
        );

    m_objectManager->Add(
        std::move(wall)
    );
}

void GameScene::CreateObjectManager()
{
    m_objectManager =
        std::make_unique<ObjectManager>();

    m_objectManager->SetColliderManager(
        m_colliderManager.get()
    );

    m_objectManager->Initialize(
        m_deviceResources
    );
}

void GameScene::CreateColliderManager()
{
    m_colliderManager = std::make_unique<ColliderManager>();
}

void GameScene::CreatePhysicsManager()
{
    m_physicsManager = std::make_unique<PhysicsManager>();
}
