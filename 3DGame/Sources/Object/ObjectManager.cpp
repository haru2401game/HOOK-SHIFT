#include "pch.h"
#include "ObjectManager.h"
#include "Sources/Component/ColliderManager.h"

void ObjectManager::Initialize(
    DX::DeviceResources* deviceResources)
{
    m_deviceResources = deviceResources;
}

void ObjectManager::SetColliderManager(
    ColliderManager* manager)
{
    m_colliderManager = manager;
}

void ObjectManager::Add(
    std::unique_ptr<GameObject> object)
{
    object->Initialize(
        m_deviceResources
    );


    if (m_colliderManager)
    {
        m_colliderManager->Register(
            &object->GetCollider()
        );
    }


    m_objects.push_back(
        std::move(object)
    );
}

void ObjectManager::Update(float deltaTime)
{
    for (auto& object : m_objects)
    {
        object->Update(deltaTime);
    }
}


void ObjectManager::Render(
    const Matrix& view,
    const Matrix& projection)
{
    for (auto& object : m_objects)
    {
        object->Render(
            view,
            projection);
    }
}