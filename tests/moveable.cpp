#include <gtest/gtest.h>

#include <Core/GameWorld.hpp>
#include <Features/SwordsmanUnit.hpp>
#include <Features/HunterUnit.hpp>

using namespace sw;

TEST(UnitMoveTest, UnitMoveBegin) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, id, x0, y0, 1, 1)));

    std::shared_ptr<IUnit>& getUnit = world.getUnitById(id);

    auto m = dynamic_cast<IMarchable*>(getUnit.get());
    uint32_t targetX = 10;
    uint32_t targetY = 10;
    uint64_t tick = world.getTick();

    testing::internal::CaptureStdout();
    m->marchTo(targetX, targetY);
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[" << tick << "] MARCH_STARTED unitId=" << id << " x=" << x0 << " y=" << y0 <<
        " targetX=" << targetX << " targetY=" << targetY << " \n";
    EXPECT_EQ(output, expected.str());
}

TEST(UnitMoveTest, UnitMoveBeginEnd) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, id, x0, y0, 1, 1)));

    std::shared_ptr<IUnit>& getUnit = world.getUnitById(id);

    auto m = dynamic_cast<IMarchable*>(getUnit.get());
    uint32_t targetX = 2;
    uint32_t targetY = 2;
    uint64_t tick = world.getTick();
    m->marchTo(targetX, targetY);

    testing::internal::CaptureStdout();
    tick = world.nextTick();
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[" << tick << "] UNIT_MOVED unitId=" << id << " x=" << targetX << " y=" << targetY << " \n" <<
        "[" << tick << "] MARCH_ENDED unitId=" << id << " x=" << targetX << " y=" << targetY << " \n";
    std::string expectedStr = expected.str();
    EXPECT_EQ(output, expected.str());
}

TEST(UnitMoveTest, UnitMoveInProgress) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, id, x0, y0, 1, 1)));

    std::shared_ptr<IUnit>& getUnit = world.getUnitById(id);

    auto m = dynamic_cast<IMarchable*>(getUnit.get());
    uint32_t targetX = 10;
    uint32_t targetY = 10;
    uint64_t tick = world.getTick();

    m->marchTo(targetX, targetY);

    testing::internal::CaptureStdout();
    tick = world.nextTick();
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[" << tick << "] UNIT_MOVED unitId=" << id << " x=2 y=3 \n";
    std::string expectedStr = expected.str();
    EXPECT_EQ(output, expected.str());
}

TEST(UnitMoveTest, UnitMoveEnd) {

}

TEST(UnitMoveTest, UnitMoveNo) {

}