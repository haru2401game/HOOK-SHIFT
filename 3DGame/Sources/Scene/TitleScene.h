#pragma once

#include "Sources/Scene/Scene.h"

class TitleScene : public Scene
{
public:
    TitleScene() = default;
    ~TitleScene() override = default;

    void Initialize() override;
    void Finalize() override;
    void Update(float deltaTime) override;
    void Render() override;
};