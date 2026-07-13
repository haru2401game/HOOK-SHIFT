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

    auto device =
        m_deviceResources->GetD3DDevice();

    auto context =
        m_deviceResources->GetD3DDeviceContext();

    m_states =
        std::make_unique<DirectX::CommonStates>(device);

    // 2D用線
    m_uiEffect =
        std::make_unique<BasicEffect>(device);

    m_uiEffect->SetVertexColorEnabled(true);

    // 3D用線
    m_lineEffect =
        std::make_unique<BasicEffect>(device);

    m_lineEffect->SetVertexColorEnabled(true);

    m_uiBatch =
        std::make_unique<
        PrimitiveBatch<VertexPositionColor>>(context);

    m_lineBatch =
        std::make_unique<
        PrimitiveBatch<VertexPositionColor>>(context);

    void const* shaderByteCode;
    size_t byteCodeLength;

    m_uiEffect->GetVertexShaderBytecode(
        &shaderByteCode,
        &byteCodeLength);

    device->CreateInputLayout(
        DirectX::VertexPositionColor::InputElements,
        DirectX::VertexPositionColor::InputElementCount,
        shaderByteCode,
        byteCodeLength,
        m_inputLayout.ReleaseAndGetAddressOf());

    m_lineEffect->GetVertexShaderBytecode(
        &shaderByteCode,
        &byteCodeLength);

    device->CreateInputLayout(
        VertexPositionColor::InputElements,
        VertexPositionColor::InputElementCount,
        shaderByteCode,
        byteCodeLength,
        m_lineInputLayout.ReleaseAndGetAddressOf());

    m_uiBatch =
        std::make_unique<
        DirectX::PrimitiveBatch<
        DirectX::VertexPositionColor>>(context);

    m_debugCube =
        DirectX::GeometricPrimitive::CreateCube(context);
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

    Player* player =
        m_objectManager->GetObject<Player>();

    if (player->GetHookGun().IsHooked())
    {
        m_hasDebugPoint = true;
        m_debugPoint = player->GetHookPoint();
    }
    else
    {
        m_hasDebugPoint = false;
    }
}

void GameScene::Render()
{
    Matrix view = m_camera->GetView();
    Matrix proj = m_camera->GetProjection();

    m_objectManager->Render(
        view,
        proj);

    if (m_hasDebugPoint)
    {
        Matrix world =
            Matrix::CreateScale(0.3f) *
            Matrix::CreateTranslation(m_debugPoint);

        m_debugCube->Draw(
            world,
            view,
            proj,
            DirectX::Colors::Red);
    }
    DrawHookWire();
    DrawCrossHair();

    if (m_hasDebugPoint)
    {
        Matrix world =
            Matrix::CreateScale(0.3f) *
            Matrix::CreateTranslation(m_debugPoint);

        m_debugCube->Draw(
            world,
            view,
            proj,
            Colors::Red);
    }
}

void GameScene::DrawHookWire()
{
    Player* player =
        m_objectManager->GetObject<Player>();

    if (!player)
        return;

    const HookGun& hook =
        player->GetHookGun();

    if (hook.GetState() == HookState::Idle)
        return;

    auto context =
        m_deviceResources->GetD3DDeviceContext();

    m_lineEffect->SetWorld(Matrix::Identity);
    m_lineEffect->SetView(m_camera->GetView());
    m_lineEffect->SetProjection(m_camera->GetProjection());

    m_lineEffect->Apply(context);

    context->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    context->IASetInputLayout(m_lineInputLayout.Get());

    context->OMSetBlendState(
        m_states->Opaque(),
        nullptr,
        0xffffffff);

    context->OMSetDepthStencilState(
        m_states->DepthDefault(),
        0);

    context->RSSetState(
        m_states->CullNone());

    m_lineBatch->Begin();

    using VPC = VertexPositionColor;

    Vector3 eye =
        player->GetEyePosition();

    Vector3 forward =
        player->GetForward();

    Vector3 right =
        player->GetRight();

    Vector3 up =
        player->GetUp();


    Vector3 start =
        eye
        + right * 0.35f
        - up * 0.25f
        + forward * 0.5f;

    Vector3 end =
        hook.GetHookPoint();

    m_lineBatch->DrawLine(
        VPC(start, Colors::Yellow),
        VPC(end, Colors::Yellow));

    m_lineBatch->End();
}

void GameScene::DrawCrossHair()
{
    auto context =
        m_deviceResources->GetD3DDeviceContext();

    auto size =
        m_deviceResources->GetOutputSize();

    float cx =
        (size.right - size.left) * 0.5f;

    float cy =
        (size.bottom - size.top) * 0.5f;

    Matrix world = Matrix::Identity;

    Matrix view = Matrix::Identity;

    Matrix projection =
        Matrix::CreateOrthographicOffCenter(
            0.0f,
            static_cast<float>(size.right - size.left),
            static_cast<float>(size.bottom - size.top),
            0.0f,
            0.0f,
            1.0f);

    m_uiEffect->SetWorld(world);
    m_uiEffect->SetView(view);
    m_uiEffect->SetProjection(projection);

    m_uiEffect->Apply(context);

    context->IASetInputLayout(
        m_inputLayout.Get());

    context->OMSetBlendState(
        m_states->Opaque(),
        nullptr,
        0xffffffff);

    context->OMSetDepthStencilState(
        m_states->DepthNone(),
        0);

    context->OMSetBlendState(
        m_states->Opaque(),
        nullptr,
        0xffffffff);

    context->OMSetDepthStencilState(
        m_states->DepthDefault(),
        0);

    context->RSSetState(
        m_states->CullNone());

    m_uiBatch->Begin();

    constexpr float length = 8.0f;
    constexpr float gap = 3.0f;

    using VPC = DirectX::VertexPositionColor;

    // クロスヘア描画
    m_uiBatch->DrawLine(
        VPC(Vector3(cx, cy - gap - length, 0), Colors::White),
        VPC(Vector3(cx, cy - gap, 0), Colors::White));
    m_uiBatch->DrawLine(
        VPC(Vector3(cx, cy + gap, 0), Colors::White),
        VPC(Vector3(cx, cy + gap + length, 0), Colors::White));
    m_uiBatch->DrawLine(
        VPC(Vector3(cx - gap - length, cy, 0), Colors::White),
        VPC(Vector3(cx - gap, cy, 0), Colors::White));
    m_uiBatch->DrawLine(
        VPC(Vector3(cx + gap, cy, 0), Colors::White),
        VPC(Vector3(cx + gap + length, cy, 0), Colors::White));

    m_uiBatch->End();
}

void GameScene::SetDebugPoint(
    const Vector3& point)
{
    m_debugPoint = point;
    m_hasDebugPoint = true;
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
    // プレイヤー
    auto player =
        std::make_unique<Player>();

    m_objectManager->Add(
        std::move(player)
    );

    // 床
    auto floor =
        std::make_unique<Floor>(
            Vector3(0, -0.5f, 0),
            Vector3(50, 1, 50)
        );
    floor->GetRigidBody().SetStatic(true);
    floor->GetRigidBody().SetUseGravity(false);
    m_objectManager->Add(std::move(floor));


    // 壁
    // 奥
    auto wall1 =
        std::make_unique<Wall>(
            Vector3(0, 5, 25),
            Vector3(50, 10, 1)
        );
    wall1->GetRigidBody().SetStatic(true);
    wall1->GetRigidBody().SetUseGravity(false);
    m_objectManager->Add(std::move(wall1));

    // 手前
    auto wall2 =
        std::make_unique<Wall>(
            Vector3(0, 5, -25),
            Vector3(50, 10, 1)
        );
    wall2->GetRigidBody().SetStatic(true);
    wall2->GetRigidBody().SetUseGravity(false);
    m_objectManager->Add(std::move(wall2));


    // 左
    auto wall3 =
        std::make_unique<Wall>(
            Vector3(-25, 5, 0),
            Vector3(1, 10, 50)
        );
    wall3->GetRigidBody().SetStatic(true);
    wall3->GetRigidBody().SetUseGravity(false);
    m_objectManager->Add(std::move(wall3));


    // 右
    auto wall4 =
        std::make_unique<Wall>(
            Vector3(25, 5, 0),
            Vector3(1, 10, 50)
        );
    wall4->GetRigidBody().SetStatic(true);
    wall4->GetRigidBody().SetUseGravity(false);
    m_objectManager->Add(std::move(wall4));



    // テスト用障害物
    auto block1 =
        std::make_unique<Wall>(
            Vector3(0, 2, 5),
            Vector3(2, 4, 8)
        );
    block1->GetRigidBody().SetStatic(true);
    block1->GetRigidBody().SetUseGravity(false);
    m_objectManager->Add(std::move(block1));


    auto block2 =
        std::make_unique<Wall>(
            Vector3(8, 3, 12),
            Vector3(3, 6, 3)
        );
    block2->GetRigidBody().SetStatic(true);
    block2->GetRigidBody().SetUseGravity(false);
    m_objectManager->Add(std::move(block2));


    auto block3 =
        std::make_unique<Wall>(
            Vector3(-10, 1.5f, 8),
            Vector3(4, 3, 10)
        );
    block3->GetRigidBody().SetStatic(true);
    block3->GetRigidBody().SetUseGravity(false);
    m_objectManager->Add(std::move(block3));


    auto block4 =
        std::make_unique<Wall>(
            Vector3(12, 4, -5),
            Vector3(2, 8, 5)
        );
    block4->GetRigidBody().SetStatic(true);
    block4->GetRigidBody().SetUseGravity(false);
    m_objectManager->Add(std::move(block4));


    auto block5 =
        std::make_unique<Wall>(
            Vector3(-15, 5, -10),
            Vector3(3, 10, 3)
        );
    block5->GetRigidBody().SetStatic(true);
    block5->GetRigidBody().SetUseGravity(false);
    m_objectManager->Add(std::move(block5));
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
