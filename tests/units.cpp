#include <gtest/gtest.h>

#include <Core/GameMap.hpp>
#include <Features/SwordsManUnit.hpp>
#include <Features/HunterUnit.hpp>

using namespace sw;

TEST(UnitSpawnTest, SpawnSwordsMan) {
    //Create a map
    GameMap gameMap(10, 10);
    //Spawn a unit with SwordsMan type
    std::unique_ptr<BaseUnit> demoUnit = std::unique_ptr<BaseUnit>(new SwordsManUnit(1, 2));
    uint32_t id = gameMap.addUnit(demoUnit);
    //Check if the map has this unit

    std::unique_ptr<BaseUnit>& getUnit = gameMap.getUnit(id);
    EXPECT_TRUE(dynamic_cast<SwordsManUnit*>(getUnit.get()) != nullptr);
}

TEST(UnitSpawnTest, SpawnHunter) {
    //Create a map
    //Spawn a unit with Hunter type
    //Check if the map has this unit
    //Create a map
    GameMap gameMap(10, 10);
    //Spawn a unit with SwordsMan type
    std::unique_ptr<BaseUnit> demoUnit = std::unique_ptr<BaseUnit>(new HunterUnit(1, 2));
    uint32_t id = gameMap.addUnit(demoUnit);
    //Check if the map has this unit

    std::unique_ptr<BaseUnit>& getUnit = gameMap.getUnit(id);
    EXPECT_TRUE(dynamic_cast<HunterUnit*>(getUnit.get()) != nullptr);
}

TEST(UnitDieTest, DieSwordsMan) {
    //Create a map
    //Spawn a unit with SwordsMan type and live for 1 turn
    //Do next turn
    //Check if unit has died
}

TEST(UnitDieTest, DieHunter) {
    //Create a map
    //Spawn a unit with Hunter type and live for 1 turn
    //Do next turn
    //Check if unit has died
}