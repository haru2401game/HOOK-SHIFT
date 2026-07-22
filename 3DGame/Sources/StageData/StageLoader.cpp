#include "pch.h"
#include "StageLoader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

StageData StageLoader::Load(const std::string& fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        throw std::runtime_error("ステージファイルを開けません");
    }

    std::stringstream ss;
    ss << file.rdbuf();

    return ParseJson(ss.str());
}

StageData StageLoader::ParseJson(const std::string& jsonText)
{
    json root = json::parse(jsonText);

    StageData stage;

    //----------------------------------------
    // Player Spawn
    //----------------------------------------

    if (root.contains("playerSpawn"))
    {
        auto spawn = root["playerSpawn"];

        stage.playerSpawn =
        {
            spawn[0].get<float>(),
            spawn[1].get<float>(),
            spawn[2].get<float>()
        };
    }

    //----------------------------------------
    // City
    //----------------------------------------

    if (root.contains("city"))
    {
        stage.hasCity = true;

        auto city = root["city"];

        if (city.contains("seed"))
            stage.city.seed = city["seed"].get<unsigned int>();

        if (city.contains("size"))
            stage.city.size = city["size"].get<float>();

        if (city.contains("blockSize"))
            stage.city.blockSize = city["blockSize"].get<float>();

        if (city.contains("roadWidth"))
            stage.city.roadWidth = city["roadWidth"].get<float>();
    }

    //----------------------------------------
    // Objects
    //----------------------------------------

    if (root.contains("objects"))
    {
        for (const auto& obj : root["objects"])
        {
            StageObjectData data;

            data.type = obj["type"].get<std::string>();

            auto pos = obj["position"];

            data.position =
            {
                pos[0].get<float>(),
                pos[1].get<float>(),
                pos[2].get<float>()
            };

            if (obj.contains("scale"))
            {
                auto scale = obj["scale"];

                data.scale =
                {
                    scale[0].get<float>(),
                    scale[1].get<float>(),
                    scale[2].get<float>()
                };
            }

            if (obj.contains("rotation"))
            {
                auto rot = obj["rotation"];

                data.rotation =
                {
                    rot[0].get<float>(),
                    rot[1].get<float>(),
                    rot[2].get<float>()
                };
            }

            if (obj.contains("color"))
            {
                auto color = obj["color"];

                data.color =
                {
                    color[0].get<float>(),
                    color[1].get<float>(),
                    color[2].get<float>()
                };
            }

            stage.objects.push_back(data);
        }
    }

    return stage;
}