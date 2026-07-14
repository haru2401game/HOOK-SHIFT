#include "Sources/StageData/StageData.h"
#include <Sources/Object/ObjectManager.h>

class StageBuilder
{
public:

    void Build(
        const StageData& stage,
        ObjectManager& objectManager);
};