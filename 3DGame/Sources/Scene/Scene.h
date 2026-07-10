#pragma once
#include <DeviceResources.h>

enum class SceneType
{
    None,
    Title,
    Game,
};

class Scene
{
public:

    Scene() = default;
    virtual ~Scene() = default;

    virtual void Initialize() {}
    virtual void Finalize() {}

    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

    void SetDeviceResources(DX::DeviceResources* device)
    {
        m_deviceResources = device;
    }

    SceneType GetNextScene() const { return m_nextScene; }

protected:
    SceneType m_nextScene = SceneType::None;

    DX::DeviceResources* m_deviceResources = nullptr;
};