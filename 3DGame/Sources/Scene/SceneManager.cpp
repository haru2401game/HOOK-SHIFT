#include "pch.h"
#include "Sources/Scene/SceneManager.h"
#include "Sources/Scene/TitleScene.h"
#include "Sources/Scene/GameScene.h"

void SceneManager::Initialize()
{
    ChangeScene(std::make_unique<TitleScene>()); // タイトルシーンに設定
}

void SceneManager::Finalize()
{
}

void SceneManager::Update(float deltaTime)
{
    if (!m_currentScene)
    {
        return;
    }

    m_currentScene->Update(deltaTime);

    switch (m_currentScene->GetNextScene())
    {
    case SceneType::Game:
        ChangeScene(std::make_unique<GameScene>());
        break;
    }
}

void SceneManager::Render()
{
    if (m_currentScene)
    {
        m_currentScene->Render();
    }
}

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
    // 変更前のシーン終了処理
    if (m_currentScene)
    {
        m_currentScene->Finalize();
    }

    // シーンの遷移
    m_currentScene = std::move(newScene);

	// 変更後のシーン初期化処理
    if (m_currentScene)
    {
        m_currentScene->SetDeviceResources(m_deviceResources);
        m_currentScene->Initialize();
    }
}

void SceneManager::SetDeviceResources(DX::DeviceResources* deviceResources)
{
    m_deviceResources = deviceResources;
}