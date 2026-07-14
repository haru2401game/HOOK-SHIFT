#include "Sources/StageData/StageData.h"

class StageLoader
{
public:

    StageData Load(const std::string& fileName);

private:

    StageData ParseJson(const std::string& jsonText);
};