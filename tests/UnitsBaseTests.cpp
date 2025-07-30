#include <gtest/gtest.h>

#include <Core/GameWorld.hpp>
#include <Features/Units/SwordsmanUnit.hpp>
#include <Features/Units/HunterUnit.hpp>

using namespace sw;

TEST(UnitsBaseTest, SpawnSwordsman) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, 0, 1, 2, 1, 1)));

    std::shared_ptr<IUnit>& getUnit = world.getUnitById(id);
    EXPECT_TRUE(dynamic_cast<SwordsmanUnit*>(getUnit.get()) != nullptr);
}

TEST(UnitsBaseTest, SwordsmanMarchable) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, 0, 1, 2, 1, 1)));

    std::shared_ptr<IUnit>& getUnit = world.getUnitById(id);
    EXPECT_TRUE(dynamic_cast<IMarchable*>(getUnit.get()) != nullptr);
}

TEST(UnitsBaseTest, SwordsmanHealthable) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, 0, 1, 2, 1, 1)));

    std::shared_ptr<IUnit>& getUnit = world.getUnitById(id);
    EXPECT_TRUE(dynamic_cast<IHealthable*>(getUnit.get()) != nullptr);
}

TEST(UnitsBaseTest, SwordsmanAttackableClose) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, 0, 1, 2, 1, 1)));

    std::shared_ptr<IUnit>& getUnit = world.getUnitById(id);
    EXPECT_TRUE(dynamic_cast<IStrengthable*>(getUnit.get()) != nullptr);
}

TEST(UnitsBaseTest, HunterMarchable) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, 0, 1, 2, 1, 1, 1, 1)));

    std::shared_ptr<IUnit>& getUnit = world.getUnitById(id);
    EXPECT_TRUE(dynamic_cast<IMarchable*>(getUnit.get()) != nullptr);
}

TEST(UnitsBaseTest, HunterHealthable) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, 0, 1, 2, 1, 1, 1, 1)));

    std::shared_ptr<IUnit>& getUnit = world.getUnitById(id);
    EXPECT_TRUE(dynamic_cast<IHealthable*>(getUnit.get()) != nullptr);
}

TEST(UnitsBaseTest, HunterAttackableClose) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, 0, 1, 2, 1, 1, 1, 1)));

    std::shared_ptr<IUnit>& getUnit = world.getUnitById(id);
    EXPECT_TRUE(dynamic_cast<IStrengthable*>(getUnit.get()) != nullptr);
}

TEST(UnitsBaseTest, GetUnitEmptyWorld) {
    GameWorld world;
    world.createMap(10, 10);
    EXPECT_ANY_THROW(world.getUnitById(0));
}

TEST(UnitsBaseTest, GetUnitIncorrectId) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, id, 1, 2, 1, 1)));

    EXPECT_ANY_THROW(world.getUnitById(10));
}

TEST(UnitsBaseTest, EventSpawnSwordsman) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    
    testing::internal::CaptureStdout();
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, id, x0, y0, 1, 1)));
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[1] UNIT_SPAWNED unitId=" << id << " unitType=Swordsman x=" << x0 << " y=" << y0 << " \n";
    EXPECT_EQ(output, expected.str());
}

TEST(UnitsBaseTest, SpawnHunter) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, id, 1, 2, 1, 1, 1, 1)));
 
    std::shared_ptr<IUnit>& getUnit = world.getUnitById(id);
    EXPECT_TRUE(dynamic_cast<HunterUnit*>(getUnit.get()) != nullptr);
}

TEST(UnitsBaseTest, EventSpawnHunter) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    
    testing::internal::CaptureStdout();
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, id, x0, y0, 1, 1, 1, 1)));
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[1] UNIT_SPAWNED unitId=" << id << " unitType=Hunter x=" << x0 << " y=" << y0 << " \n";
    EXPECT_EQ(output, expected.str());
}

TEST(UnitsBaseTest, SpawnSamePosition) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, id, 0, 0, 1, 1, 1, 1)));
    EXPECT_ANY_THROW(world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, id, 0, 0, 1, 1))));
}

TEST(UnitsBaseTest, SpawnSameId) {
    GameWorld world;
    world.createMap(10, 10);
    uint32_t id = 0;
    
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, id, 0, 0, 1, 1, 1, 1)));
    EXPECT_ANY_THROW(world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, id, 0, 1, 1, 1))));
}

TEST(UnitsBaseTest, MultipleUnitsCheckIds) {
    GameWorld world;
    world.createMap(10, 10);
    
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, 0, 0, 0, 1, 1, 1, 1)));
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, 1, 0, 1, 1, 1)));
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, 2, 1, 1, 1, 1, 1, 1)));

    std::shared_ptr<IUnit>& demoUnit1 = world.getUnitById(0);
    std::shared_ptr<IUnit>& demoUnit2 = world.getUnitById(1);
    std::shared_ptr<IUnit>& demoUnit3 = world.getUnitById(2);
    EXPECT_TRUE(dynamic_cast<HunterUnit*>(demoUnit1.get()) != nullptr);
    EXPECT_TRUE(dynamic_cast<SwordsmanUnit*>(demoUnit2.get()) != nullptr);
    EXPECT_TRUE(dynamic_cast<HunterUnit*>(demoUnit3.get()) != nullptr);
}