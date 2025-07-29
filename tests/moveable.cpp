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
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, id, x0, y0, 1, 1)));

    std::shared_ptr<IUnit>& unit = world.getUnitById(id);

    auto m = dynamic_cast<IMarchable*>(unit.get());
    uint32_t targetX = 5;
    uint32_t targetY = 5;

    testing::internal::CaptureStdout();
    m->marchTo(targetX, targetY);
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[1] MARCH_STARTED unitId=" << id << " x=" << x0 << " y=" << y0 <<
        " targetX=" << targetX << " targetY=" << targetY << " \n";
    EXPECT_EQ(output, expected.str());
}

TEST(UnitMoveTest, UnitGetAtPosInitial) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, id, x0, y0, 1, 1)));

    std::shared_ptr<IUnit>& unit = world.getUnitAtPos(x0, y0);

    EXPECT_EQ(unit->getId(), id);
    EXPECT_EQ(unit->getX(), x0);
    EXPECT_EQ(unit->getY(), y0);
}

TEST(UnitMoveTest, UnitGetAtPosMoved) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    std::shared_ptr<IUnit> unit(new SwordsmanUnit(world, id, x0, y0, 1, 1));
    world.addUnit(unit);

    auto m = dynamic_cast<IMarchable*>(unit.get());
    uint32_t targetX = 5;
    uint32_t targetY = 5;
    m->marchTo(targetX, targetY);
    m->doMarch();

    EXPECT_ANY_THROW(world.getUnitAtPos(x0, y0));

    std::shared_ptr<IUnit>& target = world.getUnitAtPos(2, 3);

    EXPECT_EQ(target->getId(), id);
}

TEST(UnitMoveTest, UnitMoveIncorrectDestination) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, id, x0, y0, 1, 1)));

    std::shared_ptr<IUnit>& unit = world.getUnitById(id);

    auto m = dynamic_cast<IMarchable*>(unit.get());
    uint32_t targetX = 10;
    uint32_t targetY = 10;
    uint64_t tick = world.getTick();

    EXPECT_ANY_THROW(m->marchTo(targetX, targetY));
}

TEST(UnitMoveTest, UnitMoveBeginEnd) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, id, x0, y0, 1, 1)));

    std::shared_ptr<IUnit>& unit = world.getUnitById(id);

    auto m = dynamic_cast<IMarchable*>(unit.get());
    uint32_t targetX = 2;
    uint32_t targetY = 2;
    m->marchTo(targetX, targetY);

    testing::internal::CaptureStdout();
    m->doMarch();
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[1] UNIT_MOVED unitId=" << id << " x=" << targetX << " y=" << targetY << " \n" <<
        "[1] MARCH_ENDED unitId=" << id << " x=" << targetX << " y=" << targetY << " \n";
    std::string expectedStr = expected.str();
    EXPECT_EQ(output, expected.str());
}

TEST(UnitMoveTest, UnitMoveInProgress) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t id = 0;
    uint32_t x0 = 1;
    uint32_t y0 = 2;
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, id, x0, y0, 1, 1)));

    std::shared_ptr<IUnit>& unit = world.getUnitById(id);

    auto m = dynamic_cast<IMarchable*>(unit.get());
    uint32_t targetX = 5;
    uint32_t targetY = 5;
    m->marchTo(targetX, targetY);

    testing::internal::CaptureStdout();
    m->doMarch();
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[1] UNIT_MOVED unitId=" << id << " x=2 y=3 \n";
    std::string expectedStr = expected.str();
    EXPECT_EQ(output, expected.str());
}