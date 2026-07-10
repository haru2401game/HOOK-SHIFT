#include "pch.h"
#include "TitleScene.h"

void TitleScene::Initialize()
{
}

void TitleScene::Finalize()
{
}

void TitleScene::Update(float deltaTime)
{
    if (Input::GetKeyDown(VK_SPACE))
    {
        m_nextScene = SceneType::Game;
    }
}

void TitleScene::Render()
{
}
