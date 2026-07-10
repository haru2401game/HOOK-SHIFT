#pragma once

#include <vector>
#include <memory>

#include "Sources/Object/GameObject.h"

class ColliderManager;

class ObjectManager
{
public:
    void Initialize(
        DX::DeviceResources* deviceResources);

    void SetColliderManager(
        ColliderManager* manager);

    void Add(
        std::unique_ptr<GameObject> object);

    void Update(float deltaTime);

    void Render(
        const Matrix& view,
        const Matrix& projection);

    const std::vector<std::unique_ptr<GameObject>>& GetObjects() const { return m_objects; };

    template<class T>
    T* GetObject()
    {
        for (auto& object : m_objects)
        {
            T* target =
                dynamic_cast<T*>(object.get());


            if (target)
            {
                return target;
            }
        }
        return nullptr;
    }

private:
    DX::DeviceResources* m_deviceResources = nullptr;
    std::vector<std::unique_ptr<GameObject>> m_objects;

    ColliderManager* m_colliderManager = nullptr;
};