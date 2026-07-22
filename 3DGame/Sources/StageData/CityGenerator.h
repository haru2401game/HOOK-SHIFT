#pragma once

#include <random>
#include "StageData.h"

class ObjectManager;

class CityGenerator
{
public:

    void Generate(
        ObjectManager& objectManager,
        const CityData& city);

private:

    void GenerateGround(ObjectManager&);
    void GenerateRoads(ObjectManager&);
    void GenerateBuildings(ObjectManager&);
    void GenerateGoal(ObjectManager&);

    std::mt19937 m_random;
};