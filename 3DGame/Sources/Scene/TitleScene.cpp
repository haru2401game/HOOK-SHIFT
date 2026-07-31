#include "pch.h"
#include "TitleScene.h"

void TitleScene::Initialize()
{
    CreateColliderManager();
    CreateObjectManager();
    CreateObjects();
    CreateCamera();


    auto context =
        m_deviceResources->GetD3DDeviceContext();


    m_spriteBatch =
        std::make_unique<DirectX::SpriteBatch>(
            context);


    LoadLogo();

    auto device =
        m_deviceResources->GetD3DDevice();


    m_font =
        std::make_unique<DirectX::SpriteFont>(
            device,
            L"Resources/Fonts/SegoeUI_18.spritefont");
}

void TitleScene::Finalize()
{
}

void TitleScene::Update(float deltaTime)
{
    m_objectManager->Update(deltaTime);


    UpdateCamera(deltaTime);

    UpdateLogo(deltaTime);


    if (Input::GetKeyDown(VK_SPACE))
    {
        m_nextScene = SceneType::Game;
    }
}

void TitleScene::Render()
{
    Matrix view =
        m_camera->GetView();

    Matrix proj =
        m_camera->GetProjection();


    m_objectManager->Render(
        view,
        proj);



    m_spriteBatch->Begin();


    RECT size =
        m_deviceResources->GetOutputSize();


    float screenWidth =
        static_cast<float>(
            size.right - size.left);


    float screenHeight =
        static_cast<float>(
            size.bottom - size.top);



    float offsetY =
        sinf(
            m_logoTime *
            LOGO_FLOAT_SPEED)
        *
        LOGO_FLOAT_RANGE;



    Vector2 position
    (
        (screenWidth - m_logoSize.x)
        * 0.5f,

        (screenHeight - m_logoSize.y)
        * 0.5f
        +
        offsetY
    );


    m_spriteBatch->Draw(
        m_logoTexture.Get(),
        position);

    // PRESS ANY KEY

    float alpha =
        (sinf(
            m_pressTime *
            PRESS_BLINK_SPEED)
            + 1.0f)
        * 0.5f;


    // 最小透明度を設定
    alpha =
        PRESS_ALPHA_MIN +
        alpha *
        (1.0f - PRESS_ALPHA_MIN);


    const wchar_t* text =
        L"PRESS SPACE KEY";


    Vector2 textSize =
        m_font->MeasureString(text);


    Vector2 textPosition
    (
        (screenWidth - textSize.x)
        * 0.5f,

        screenHeight * 0.75f
    );


    m_font->DrawString(
        m_spriteBatch.get(),
        text,
        textPosition,
        DirectX::Colors::White,
        0.0f,
        Vector2::Zero,
        1.0f,
        DirectX::SpriteEffects_None,
        0.0f
    );


    m_spriteBatch->End();
}

void TitleScene::CreateCamera()
{
    auto size = m_deviceResources->GetOutputSize();

    float aspect =
        static_cast<float>(size.right - size.left) /
        static_cast<float>(size.bottom - size.top);

    m_camera = std::make_unique<Camera>();

    m_camera->SetAspectRatio(aspect);

    m_camera->SetFixedCamera(
        { 0.0f, 700.0f, -700.0f },   // カメラ位置
        { 0.0f, 300.0f, 0.0f });       // 注視点
}

void TitleScene::CreateObjects()
{
    StageData stage =
        m_stageLoader.Load(
            "Resources/Stages/Stage1.json");

    // ステージのみ生成
    m_stageBuilder.Build(
        stage,
        *m_objectManager);
}

void TitleScene::CreateObjectManager()
{
    m_objectManager =
        std::make_unique<ObjectManager>();

    m_objectManager->SetColliderManager(
        m_colliderManager.get());

    m_objectManager->Initialize(
        m_deviceResources);
}

void TitleScene::CreateColliderManager()
{
    m_colliderManager =
        std::make_unique<ColliderManager>();
}

void TitleScene::UpdateCamera(float deltaTime)
{
    m_cameraAngle +=
        CAMERA_SPEED * deltaTime;


    Vector3 position;

    position.x =
        CAMERA_TARGET.x +
        cosf(m_cameraAngle) *
        CAMERA_RADIUS_X;


    position.y =
        CAMERA_HEIGHT;


    position.z =
        CAMERA_TARGET.z +
        sinf(m_cameraAngle) *
        CAMERA_RADIUS_Z;


    m_camera->SetFixedCamera(
        position,
        CAMERA_TARGET);
}

void TitleScene::UpdateLogo(float deltaTime)
{
    m_logoTime += deltaTime;

    m_pressTime += deltaTime;
}

void TitleScene::LoadLogo()
{
    auto device =
        m_deviceResources->GetD3DDevice();


    DirectX::CreateWICTextureFromFile(
        device,
        L"Resources/Textures/TitleLogo.png",
        nullptr,
        m_logoTexture.ReleaseAndGetAddressOf());


    Microsoft::WRL::ComPtr<ID3D11Resource> resource;

    m_logoTexture->GetResource(
        resource.GetAddressOf());


    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;

    resource.As(&texture);


    D3D11_TEXTURE2D_DESC desc{};

    texture->GetDesc(&desc);


    m_logoSize =
    {
        static_cast<float>(desc.Width),
        static_cast<float>(desc.Height)
    };
}
