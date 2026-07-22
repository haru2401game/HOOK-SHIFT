#include "pch.h"
#include "CityGenerator.h"

#include "Sources/Object/Floor.h"
#include "Sources/Object/Wall.h"
#include "Sources/Object/ObjectManager.h"

namespace
{
    constexpr float CITY_SIZE = 1000.0f;
    constexpr float ROAD_WIDTH = 40.0f;
    constexpr float BLOCK_SIZE = 120.0f;
}

void CityGenerator::Generate(
    ObjectManager& objectManager,
    const CityData& city)
{
    m_random.seed(city.seed);

    GenerateGround(objectManager);
    GenerateRoads(objectManager);
    GenerateBuildings(objectManager);
    GenerateGoal(objectManager);
}

void CityGenerator::GenerateGround(
    ObjectManager& objectManager)
{
    auto floor =
        std::make_unique<Floor>(
            Vector3(0, -0.5f, 0),
            Vector3(CITY_SIZE, 1, CITY_SIZE));

    floor->SetColor({ 0.22f,0.22f,0.22f });
    floor->GetRigidBody().SetStatic(true);

    objectManager.Add(std::move(floor));
}

void CityGenerator::GenerateRoads(
    ObjectManager& objectManager)
{
    //-------------------------
    // 縦道路
    //-------------------------

    for (float x = -480;x <= 480;x += BLOCK_SIZE)
    {
        auto road =
            std::make_unique<Floor>(
                Vector3(x, -0.49f, 0),
                Vector3(ROAD_WIDTH, 1, CITY_SIZE));

        road->SetColor({ 0.1f,0.1f,0.1f });
        road->GetRigidBody().SetStatic(true);

        objectManager.Add(std::move(road));
    }

    //-------------------------
    // 横道路
    //-------------------------

    for (float z = -480;z <= 480;z += BLOCK_SIZE)
    {
        auto road =
            std::make_unique<Floor>(
                Vector3(0, -0.49f, z),
                Vector3(CITY_SIZE, 1, ROAD_WIDTH));

        road->SetColor({ 0.1f,0.1f,0.1f });
        road->GetRigidBody().SetStatic(true);

        objectManager.Add(std::move(road));
    }
}

void CityGenerator::GenerateBuildings(
    ObjectManager& objectManager)
{
    std::uniform_real_distribution<float> heightDist(80.0f, 320.0f);
    std::uniform_real_distribution<float> sizeDist(35.0f, 70.0f);
    std::uniform_real_distribution<float> colorDist(0.28f, 0.46f);
    std::uniform_real_distribution<float> offsetDist(-12.0f, 12.0f);
    std::uniform_int_distribution<int> typeDist(0, 3);

    constexpr float BUILDING_AREA = BLOCK_SIZE - ROAD_WIDTH;

    for (float bx = -420.0f; bx <= 420.0f; bx += BLOCK_SIZE)
    {
        for (float bz = -420.0f; bz <= 420.0f; bz += BLOCK_SIZE)
        {
            int pattern = typeDist(m_random);

            int count = 1;

            switch (pattern)
            {
            case 0: count = 1; break;
            case 1: count = 2; break;
            case 2: count = 3; break;
            case 3: count = 4; break;
            }

            std::vector<Vector3> offsets;

            if (count == 1)
            {
                offsets.push_back({ 0,0,0 });
            }
            else if (count == 2)
            {
                offsets.push_back({ -18,0,0 });
                offsets.push_back({ 18,0,0 });
            }
            else if (count == 3)
            {
                offsets.push_back({ -18,0,-18 });
                offsets.push_back({ 18,0,-18 });
                offsets.push_back({ 0,0,18 });
            }
            else
            {
                offsets.push_back({ -18,0,-18 });
                offsets.push_back({ 18,0,-18 });
                offsets.push_back({ -18,0,18 });
                offsets.push_back({ 18,0,18 });
            }

            for (const auto& offset : offsets)
            {
                float height = heightDist(m_random);

                float width = sizeDist(m_random);
                float depth = sizeDist(m_random);

                float color = colorDist(m_random);

                float x =
                    bx +
                    offset.x +
                    offsetDist(m_random);

                float z =
                    bz +
                    offset.z +
                    offsetDist(m_random);

                auto building =
                    std::make_unique<Wall>(
                        Vector3(
                            x,
                            height * 0.5f,
                            z),
                        Vector3(
                            width,
                            height,
                            depth));

                building->SetColor(
                    {
                        color,
                        color,
                        color + 0.02f
                    });

                building->GetRigidBody().SetStatic(true);

                objectManager.Add(
                    std::move(building));
            }
        }
    }
}

void CityGenerator::GenerateGoal(
    ObjectManager& objectManager)
{
    auto goal =
        std::make_unique<Wall>(
            Vector3(420, 300, 420),
            Vector3(80, 600, 80));

    goal->SetColor({ 0.9f,0.9f,0.95f });

    goal->GetRigidBody().SetStatic(true);

    objectManager.Add(std::move(goal));

    auto roof =
        std::make_unique<Floor>(
            Vector3(420, 600, 420),
            Vector3(70, 1, 70));

    roof->SetColor({ 0.8f,0.8f,0.8f });

    roof->GetRigidBody().SetStatic(true);

    objectManager.Add(std::move(roof));
}