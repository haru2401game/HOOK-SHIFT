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
    // リセット
    if (Input::GetKeyDown('R'))
    {
        ResetStage();
        return;
    }

    Player* player = m_objectManager->GetObject<Player>();

    // オブジェクト更新
    m_objectManager->Update(deltaTime);

    // 物理処理更新
    m_physicsManager->Update(
        *m_objectManager,
        *m_colliderManager,
        deltaTime);

    // カメラ関連更新
    m_camera->Update(deltaTime);

    // フックポイント更新
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

    Player* player =
        m_objectManager->GetObject<Player>();

    auto size =
        m_deviceResources->GetOutputSize();

    float aspect =
        static_cast<float>(size.right - size.left) /
        static_cast<float>(size.bottom - size.top);

    Matrix gunProjection =
        Matrix::CreatePerspectiveFieldOfView(
            XMConvertToRadians(70.0f),
            aspect,
            0.01f,
            100.0f);

    // ステージの描画
    m_objectManager->Render(
        view,
        proj);

    // ワイヤーの描画
    DrawHookWire();

    // フックガンモデルの描画
    player->RenderViewModel(gunProjection);

    if (m_hasDebugPoint)
    {
        Matrix world =
            Matrix::CreateScale(0.3f) *
            Matrix::CreateTranslation(m_debugPoint);

        // フックポイントの描画
        m_debugCube->Draw(
            world,
            view,
            proj,
            DirectX::Colors::Red);
    }

    // クロスヘアの描画
    DrawCrossHair();
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

    Vector3 start =
        player->GetWorldMuzzlePosition();

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

void GameScene::ResetStage()
{
    CreateColliderManager();
    CreateObjectManager();
    CreatePhysicsManager();
    CreateObjects();
    CreateCamera();

    m_hasDebugPoint = false;
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
    StageData stage =
        m_stageLoader.Load(
            "Resources/Stages/Stage1.json");

    // プレイヤー
    auto player =
        std::make_unique<Player>();

    player->SetPosition(stage.playerSpawn);

    m_objectManager->Add(
        std::move(player));

    // ステージ生成
    m_stageBuilder.Build(
        stage,
        *m_objectManager);
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
