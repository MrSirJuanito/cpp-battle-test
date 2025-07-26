#include <gtest/gtest.h>

#include <Core/GameWorld.hpp>
#include <Features/SwordsManUnit.hpp>
#include <Features/HunterUnit.hpp>

using namespace sw;

TEST(UnitSpawnTest, SpawnSwordsMan) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new SwordsManUnit(world, 0, 1, 2)));

    std::shared_ptr<IUnit>& getUnit = world.getUnit(id);
    EXPECT_TRUE(dynamic_cast<SwordsManUnit*>(getUnit.get()) != nullptr);
}

TEST(UnitSpawnTest, GetUnitEmptyWorld) {
    GameWorld world;
    world.createMap(10, 10);
    EXPECT_ANY_THROW(world.getUnit(0));
}

TEST(UnitSpawnTest, GetUnitIncorrectId) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new SwordsManUnit(world, id, 1, 2)));

    EXPECT_ANY_THROW(world.getUnit(10));
}

TEST(UnitSpawnTest, EventSpawnSwordsMan) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    
    testing::internal::CaptureStdout();
    world.addUnit(std::shared_ptr<IUnit>(new SwordsManUnit(world, id, x0, y0)));
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[0] UNIT_SPAWNED unitId=" << id << " unitType=Swordsman x=" << x0 << " y=" << y0 << " \n";
    EXPECT_EQ(output, expected.str());
}

TEST(UnitSpawnTest, SpawnHunter) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, id, 1, 2)));
 
    std::shared_ptr<IUnit>& getUnit = world.getUnit(id);
    EXPECT_TRUE(dynamic_cast<HunterUnit*>(getUnit.get()) != nullptr);
}

TEST(UnitSpawnTest, EventSpawnHunter) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    
    testing::internal::CaptureStdout();
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, id, x0, y0)));
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[0] UNIT_SPAWNED unitId=" << id << " unitType=Hunter x=" << x0 << " y=" << y0 << " \n";
    EXPECT_EQ(output, expected.str());
}

TEST(UnitSpawnTest, MultipleUnitsSamePosition) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, id, 0, 0)));
    EXPECT_ANY_THROW(world.addUnit(std::shared_ptr<IUnit>(new SwordsManUnit(world, id, 0, 0))));
}

TEST(UnitSpawnTest, MultipleUnitsCheckIds) {
    GameWorld world;
    world.createMap(10, 10);
    
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, 0, 0, 0)));
    world.addUnit(std::shared_ptr<IUnit>(new SwordsManUnit(world, 1, 0, 1)));
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, 2, 1, 1)));

    std::shared_ptr<IUnit>& demoUnit1 = world.getUnit(0);
    std::shared_ptr<IUnit>& demoUnit2 = world.getUnit(1);
    std::shared_ptr<IUnit>& demoUnit3 = world.getUnit(2);
    EXPECT_TRUE(dynamic_cast<HunterUnit*>(demoUnit1.get()) != nullptr);
    EXPECT_TRUE(dynamic_cast<SwordsManUnit*>(demoUnit2.get()) != nullptr);
    EXPECT_TRUE(dynamic_cast<HunterUnit*>(demoUnit3.get()) != nullptr);
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