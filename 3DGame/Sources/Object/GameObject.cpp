#include "pch.h"
#include "GameObject.h"


GameObject::GameObject()
{
    m_collider.SetOwner(this);
}

void GameObject::SetPosition(
    const Vector3& position)
{
    m_position = position;

    UpdateCollider();
}


void GameObject::SetRotation(
    const Vector3& rotation)
{
    m_rotation = rotation;
}


void GameObject::SetScale(
    const Vector3& scale)
{
    m_scale = scale;

    m_collider.SetSize(scale);
}


void GameObject::UpdateCollider()
{
    m_collider.SetCenter(m_position);
}