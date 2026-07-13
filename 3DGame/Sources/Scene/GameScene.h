#pragma once

#include "Sources/Scene/Scene.h"

#include "Sources/Object/Camera.h"
#include "Sources/Object/ObjectManager.h"
#include "Sources/Component/ColliderManager.h"
#include <Sources/Physics/PhysicsManager.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <CommonStates.h>

class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() = default;

    void Initialize() override;
    void Finalize() override;
    void Update(float deltaTime) override;
    void Render() override;

    void DrawHookWire();
    void DrawCrossHair();

    void SetDebugPoint(
        const Vector3& point);

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

    // 2D
    std::unique_ptr<DirectX::BasicEffect> m_uiEffect;
    std::unique_ptr<DirectX::PrimitiveBatch<
        DirectX::VertexPositionColor>> m_uiBatch;

    // 3D
    std::unique_ptr<DirectX::BasicEffect> m_lineEffect;
    std::unique_ptr<DirectX::PrimitiveBatch<
        DirectX::VertexPositionColor>> m_lineBatch;

    std::unique_ptr<DirectX::CommonStates> m_states;

    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_lineInputLayout;

    std::unique_ptr<DirectX::GeometricPrimitive> m_debugCube;

    bool m_hasDebugPoint = false;
    Vector3 m_debugPoint = Vector3::Zero;
};