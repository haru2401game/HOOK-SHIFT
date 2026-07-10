#pragma once

#include "pch.h"
#include "Scene.h"

class SceneManager
{
public:

	SceneManager() = default;
	~SceneManager() = default;

    void Initialize();
    void Finalize();

	void Update(float deltaTime);
	void Render();
	void ChangeScene(std::unique_ptr<Scene> newScene);

	void SetDeviceResources(DX::DeviceResources* deviceResources);

private:

    std::unique_ptr<Scene> m_currentScene;
	DX::DeviceResources* m_deviceResources = nullptr;
};