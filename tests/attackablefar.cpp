#include <gtest/gtest.h>

#include <Core/GameWorld.hpp>
#include <Features/HunterUnit.hpp>
#include <Features/SwordsmanUnit.hpp>

using namespace sw;

TEST(UnitAttackFarTest, UnitAttackFalse) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t healthInit = 5;
    std::shared_ptr<IUnit> unit(new HunterUnit(world, 0, 3, 2, healthInit, 1, 1, 1));
    world.addUnit(unit);

    auto a = dynamic_cast<IAttackableFar*>(unit.get());
    bool attacked = a->doAttackFar();
    EXPECT_FALSE(attacked);
    
    auto h = dynamic_cast<IHealthable*>(unit.get());
    EXPECT_EQ(h->getHealth(), healthInit);
}

TEST(UnitAttackFarTest, HunterAttackInRange) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t healthInit = 5;
    uint32_t range = 5;
    std::shared_ptr<IUnit> attacker(new HunterUnit(world, 0, 2, 2, healthInit, 1, 1, range));
    world.addUnit(attacker);
    std::shared_ptr<IUnit> defender(new HunterUnit(world, 1, 2 + range, 2, healthInit, 1, 1, 1));
    world.addUnit(defender);

    auto a = dynamic_cast<IAttackableFar*>(attacker.get());
    bool attacked = a->doAttackFar();
    EXPECT_TRUE(attacked);

    auto healthAttacker = dynamic_cast<IHealthable*>(attacker.get());
    auto healthDefender = dynamic_cast<IHealthable*>(defender.get());

    EXPECT_EQ(healthAttacker->getHealth(), healthInit);
    EXPECT_EQ(healthDefender->getHealth(), healthInit - 1);
}

TEST(UnitAttackFarTest, EventHunterAttackInRange) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t attackerId = 0;
    uint32_t attackerAgility = 1;
    uint32_t targetId = 1;
    uint32_t healthInit = 5;
    uint32_t range = 5;
    std::shared_ptr<IUnit> attacker(new HunterUnit(world, attackerId, 2, 2, healthInit, 1, attackerAgility, range));
    world.addUnit(attacker);
    std::shared_ptr<IUnit> defender(new HunterUnit(world, targetId, 2 + range, 2, healthInit, 1, 1, 1));
    world.addUnit(defender);

    auto a = dynamic_cast<IAttackableFar*>(attacker.get());
    testing::internal::CaptureStdout();
    a->doAttackFar();
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[1] UNIT_ATTACKED attackerUnitId=" << attackerId << " targetUnitId=" << targetId <<
        " damage=" << attackerAgility << " targetHp=" << healthInit - 1 << " \n";
    
    EXPECT_EQ(output, expected.str());
}

TEST(UnitAttackFarTest, HunterAttackOnlyOne) {
    // TODO
}

TEST(UnitAttackFarTest, EventHunterDie) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t attackerId = 1;
    uint32_t defenderId = 2;
    uint32_t agility = 5;
    std::shared_ptr<IUnit> attacker(new HunterUnit(world, attackerId, 0, 1, 1, agility, 1, 5));
    world.addUnit(attacker);
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, defenderId, 5, 1, 5, 1)));

    testing::internal::CaptureStdout();
    auto a = dynamic_cast<IAttackableFar*>(attacker.get());
    a->doAttackFar();
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[1] UNIT_ATTACKED attackerUnitId=" << attackerId << " targetUnitId=" << defenderId << " damage=" << agility << " targetHp=0 \n" \
        "[1] UNIT_DIED unitId=" << defenderId << " \n";

    EXPECT_EQ(output, expected.str());
}