#include "pch.h"
#include "StageBuilder.h"

#include "Sources/Object/Floor.h"
#include "Sources/Object/Wall.h"

#include "Sources/StageData/CityGenerator.h"

void StageBuilder::Build(
    const StageData& stage,
    ObjectManager& objectManager)
{
    //----------------------------------------
    // JSONで配置されたオブジェクト
    //----------------------------------------

    for (const auto& obj : stage.objects)
    {
        if (obj.type == "Floor")
        {
            auto floor =
                std::make_unique<Floor>(
                    obj.position,
                    obj.scale);

            floor->SetColor(obj.color);

            floor->GetRigidBody().SetStatic(true);

            objectManager.Add(
                std::move(floor));
        }
        else if (obj.type == "Wall")
        {
            auto wall =
                std::make_unique<Wall>(
                    obj.position,
                    obj.scale);

            wall->SetColor(obj.color);

            wall->GetRigidBody().SetStatic(true);

            objectManager.Add(
                std::move(wall));
        }
    }

    //----------------------------------------
    // シードから街生成
    //----------------------------------------

    if (stage.hasCity)
    {
        CityGenerator generator;

        generator.Generate(
            objectManager,
            stage.city);
    }
}