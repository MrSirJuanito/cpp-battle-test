#include <gtest/gtest.h>

#include <memory>
#include <Core/GameWorld.hpp>
#include <Features/SwordsmanUnit.hpp>
#include <Features/HunterUnit.hpp>

using namespace sw;

TEST(IntegrationTest, TickHunterAttackFar) {
    GameWorld world;
    world.createMap(10, 10);
    
    std::shared_ptr<IUnit> hunter(new HunterUnit(world, 2, 3, 0, 10, 5, 1, 4));
    world.addUnit(hunter);
    dynamic_cast<IMarchable*>(hunter.get())->marchTo(0, 0);
    std::shared_ptr<IUnit> swordsman(new SwordsmanUnit(world, 3, 0, 2, 10, 2));
    world.addUnit(swordsman);
    dynamic_cast<IMarchable*>(swordsman.get())->marchTo(0, 0);

    testing::internal::CaptureStdout();
    world.nextTick();
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[2] UNIT_ATTACKED attackerUnitId=2 targetUnitId=3 damage=5 targetHp=5 \n"\
        "[2] UNIT_MOVED unitId=3 x=0 y=1 \n";
    
    EXPECT_EQ(output, expected.str());
}