#include "pch.h"
#include "StageBuilder.h"

#include <Sources/Object/Floor.h>
#include <Sources/Object/Wall.h>

void StageBuilder::Build(
    const StageData& stage,
    ObjectManager& objectManager)
{
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

            objectManager.Add(std::move(floor));
        }
        else if (obj.type == "Wall")
        {
            auto wall =
                std::make_unique<Wall>(
                    obj.position,
                    obj.scale);

            wall->SetColor(obj.color);

            wall->GetRigidBody().SetStatic(true);

            objectManager.Add(std::move(wall));
        }
    }
}