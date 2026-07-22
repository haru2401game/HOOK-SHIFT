#pragma once

#include <string>
#include <vector>

#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

//--------------------------------------
// ステージオブジェクト
//--------------------------------------

struct StageObjectData
{
    std::string type;

    Vector3 position;

    Vector3 scale = Vector3::One;

    Vector3 rotation = Vector3::Zero;

    Vector3 color = Vector3::One;
};

//--------------------------------------
// 街生成設定
//--------------------------------------

struct CityData
{
    // ランダムシード
    unsigned int seed = 0;

    // 街全体サイズ
    float size = 1000.0f;

    // 1ブロックの大きさ
    float blockSize = 120.0f;

    // 道路幅
    float roadWidth = 40.0f;

    // 建物高さ
    float minBuildingHeight = 80.0f;
    float maxBuildingHeight = 320.0f;

    // 建物サイズ
    float minBuildingSize = 35.0f;
    float maxBuildingSize = 70.0f;

    // ゴール位置
    Vector3 goalPosition = Vector3(420.0f, 300.0f, 420.0f);
};

//--------------------------------------
// ステージデータ
//--------------------------------------

struct StageData
{
    // プレイヤースポーン位置
    Vector3 playerSpawn = Vector3::Zero;

    // 手置きオブジェクト
    std::vector<StageObjectData> objects;

    // 街生成を行うか
    bool hasCity = false;

    // 街生成設定
    CityData city;
};