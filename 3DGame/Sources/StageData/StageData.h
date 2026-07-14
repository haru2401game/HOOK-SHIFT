#pragma once

#include <string>
#include <vector>

#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

struct StageObjectData
{
    std::string type;

    Vector3 position;

    Vector3 scale = Vector3::One;

    Vector3 rotation = Vector3::Zero;

    Vector3 color = Vector3::One;
};

struct StageData
{
    Vector3 playerSpawn;

    std::vector<StageObjectData> objects;
};