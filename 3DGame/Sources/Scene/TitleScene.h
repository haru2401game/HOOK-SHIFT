#pragma once

#include "Sources/Scene/Scene.h"

#include "Sources/Object/Camera.h"
#include "Sources/Object/ObjectManager.h"
#include "Sources/Component/ColliderManager.h"

#include "Sources/StageData/StageLoader.h"
#include "Sources/StageData/StageBuilder.h"

#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <WICTextureLoader.h>


class TitleScene : public Scene
{
public:

    TitleScene() = default;
    ~TitleScene() override = default;

    void Initialize() override;
    void Finalize() override;

    void Update(float deltaTime) override;
    void Render() override;


private:

    void CreateCamera();

    void CreateObjects();
    void CreateObjectManager();
    void CreateColliderManager();

    void UpdateCamera(float deltaTime);
    void UpdateLogo(float deltaTime);

    void LoadLogo();


private:

    // Camera

    std::unique_ptr<Camera> m_camera;

    float m_cameraAngle = 0.0f;


    // Stage

    std::unique_ptr<ObjectManager> m_objectManager;

    std::unique_ptr<ColliderManager> m_colliderManager;

    StageLoader m_stageLoader;

    StageBuilder m_stageBuilder;


    // UI

    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>
        m_logoTexture;


    DirectX::SimpleMath::Vector2 m_logoSize;

    float m_logoTime = 0.0f;

    // Press Any Key
    std::unique_ptr<DirectX::SpriteFont> m_font;

    float m_pressTime = 0.0f;


private:

    // Camera Settings

    static constexpr float CAMERA_RADIUS_X = 700.0f;
    static constexpr float CAMERA_RADIUS_Z = 500.0f;

    static constexpr float CAMERA_HEIGHT = 800.0f;

    static constexpr float CAMERA_SPEED = 0.2f;

    static constexpr DirectX::SimpleMath::Vector3
        CAMERA_TARGET =
    { 0.0f,300.0f,0.0f };


    // Logo Settings

    static constexpr float LOGO_FLOAT_SPEED = 1.5f;

    static constexpr float LOGO_FLOAT_RANGE = 10.0f;


    // Press設定
    static constexpr float PRESS_BLINK_SPEED = 2.0f;
    static constexpr float PRESS_ALPHA_MIN = 0.3f;
};