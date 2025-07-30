#include <gtest/gtest.h>

#include <Core/GameWorld.hpp>
#include <Features/HunterUnit.hpp>
#include <Features/SwordsmanUnit.hpp>

using namespace sw;

TEST(AgiliableTest, UnitAttackFalse) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t healthInit = 5;
    std::shared_ptr<IUnit> unit(new HunterUnit(world, 0, 3, 2, healthInit, 1, 1, 1));
    world.addUnit(unit);

    auto a = dynamic_cast<IAgiliable*>(unit.get());
    bool attacked = a->doAttackFar();
    EXPECT_FALSE(attacked);
    
    auto h = dynamic_cast<IHealthable*>(unit.get());
    EXPECT_EQ(h->getHealth(), healthInit);
}

TEST(AgiliableTest, HunterAttackInRange) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t healthInit = 5;
    uint32_t range = 5;
    std::shared_ptr<IUnit> attacker(new HunterUnit(world, 0, 2, 2, healthInit, 1, 1, range));
    world.addUnit(attacker);
    std::shared_ptr<IUnit> defender(new HunterUnit(world, 1, 2 + range, 2, healthInit, 1, 1, 1));
    world.addUnit(defender);

    auto a = dynamic_cast<IAgiliable*>(attacker.get());
    bool attacked = a->doAttackFar();
    EXPECT_TRUE(attacked);

    auto healthAttacker = dynamic_cast<IHealthable*>(attacker.get());
    auto healthDefender = dynamic_cast<IHealthable*>(defender.get());

    EXPECT_EQ(healthAttacker->getHealth(), healthInit);
    EXPECT_EQ(healthDefender->getHealth(), healthInit - 1);
}

TEST(AgiliableTest, EventHunterAttackInRange) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t attackerId = 0;
    uint32_t attackerAgility = 2;
    uint32_t targetId = 1;
    uint32_t healthInit = 5;
    uint32_t range = 5;
    std::shared_ptr<IUnit> attacker(new HunterUnit(world, attackerId, 2, 2, healthInit, attackerAgility, 1, range));
    world.addUnit(attacker);
    std::shared_ptr<IUnit> defender(new HunterUnit(world, targetId, 2 + range, 2, healthInit, 1, 1, 1));
    world.addUnit(defender);

    auto a = dynamic_cast<IAgiliable*>(attacker.get());
    testing::internal::CaptureStdout();
    bool attacked = a->doAttackFar();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(attacked);

    std::stringstream expected;
    expected << "[1] UNIT_ATTACKED attackerUnitId=" << attackerId << " targetUnitId=" << targetId <<
        " damage=" << attackerAgility << " targetHp=" << healthInit-attackerAgility << " \n";
    
    EXPECT_EQ(output, expected.str());
}

TEST(AgiliableTest, HunterAttackOutOfRange) {
    GameWorld world;
    world.createMap(15, 15);
    
    uint32_t attackerId = 0;
    uint32_t attackerX = 5;
    uint32_t attackerY = 5;
    uint32_t attackerAgility = 2;
    uint32_t attackerRange = 5;
    uint32_t healthInit = 5;
    uint32_t healthTotal = 0;
    std::shared_ptr<IUnit> attacker(new HunterUnit(world, attackerId, 5, 5, healthInit, attackerAgility, 1, attackerRange));
    world.addUnit(attacker);
    uint32_t targetUnitId = attackerId + 1;
    // We place target units in the points where the attacker shouldn't reach them if their range is circle
    for (uint32_t x = attackerX - attackerRange; x <= attackerX + attackerRange; x += attackerRange*2) {
        for (uint32_t y = attackerY - attackerRange; y <= attackerY + attackerRange; y += attackerRange*2) {
            std::shared_ptr<IUnit> target(new HunterUnit(world, targetUnitId++, x, y, healthInit, 1, 1, 1));
            world.addUnit(target);
            healthTotal += healthInit;
        }
    }

    auto a = dynamic_cast<IAgiliable*>(attacker.get());
    bool attacked = a->doAttackFar();
    EXPECT_FALSE(attacked);

    uint32_t healthTotalActual = 0;
    for (uint32_t id = attackerId + 1; id < targetUnitId; ++id) {
        auto h = dynamic_cast<IHealthable*>(world.getUnitById(id).get());
        healthTotalActual += h->getHealth();
    }

    EXPECT_EQ(healthTotalActual, healthTotal);
}

TEST(AgiliableTest, HunterAttackOnlyOne) {
    GameWorld world;
    world.createMap(15, 15);
    
    uint32_t attackerId = 0;
    uint32_t attackerX = 5;
    uint32_t attackerY = 5;
    uint32_t attackerAgility = 2;
    uint32_t attackerRange = 5;
    uint32_t healthInit = 5;
    uint32_t healthTotal = 0;
    std::shared_ptr<IUnit> attacker(new HunterUnit(world, attackerId, 5, 5, healthInit, attackerAgility, 1, attackerRange));
    world.addUnit(attacker);
    uint32_t targetUnitId = attackerId + 1;
    for (int coord = 0; coord <= 1; ++coord) {
        uint32_t attackerCood = (coord == 0) ? attackerX : attackerY;
        for (uint32_t p = attackerCood - attackerRange; p <= attackerCood + attackerRange; p += attackerRange*2) {
            uint32_t newX = (coord == 0) ? p : attackerX;
            uint32_t newY = (coord == 1) ? p : attackerY;
            std::shared_ptr<IUnit> target(new HunterUnit(world, targetUnitId++, newX, newY, healthInit, 1, 1, 1));
            world.addUnit(target);
            healthTotal += healthInit;
        }
    }

    auto a = dynamic_cast<IAgiliable*>(attacker.get());
    bool attacked = a->doAttackFar();
    EXPECT_TRUE(attacked);

    uint32_t healthTotalActual = 0;
    for (uint32_t id = attackerId + 1; id < targetUnitId; ++id) {
        auto h = dynamic_cast<IHealthable*>(world.getUnitById(id).get());
        healthTotalActual += h->getHealth();
    }

    // The target unit is picked randomly, so if the total actual health is less on attackerStrength
    // this means that only one unit was attacked, which is our goal
    EXPECT_EQ(healthTotalActual, healthTotal-attackerAgility);
}

TEST(AgiliableTest, EventHunterDie) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t attackerId = 1;
    uint32_t defenderId = 2;
    uint32_t agility = 5;
    std::shared_ptr<IUnit> attacker(new HunterUnit(world, attackerId, 0, 1, 1, agility, 1, 5));
    world.addUnit(attacker);
    world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, defenderId, 5, 1, 5, 1)));

    testing::internal::CaptureStdout();
    auto a = dynamic_cast<IAgiliable*>(attacker.get());
    a->doAttackFar();
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[1] UNIT_ATTACKED attackerUnitId=" << attackerId << " targetUnitId=" << defenderId << " damage=" << agility << " targetHp=0 \n" \
        "[1] UNIT_DIED unitId=" << defenderId << " \n";

    EXPECT_EQ(output, expected.str());
}