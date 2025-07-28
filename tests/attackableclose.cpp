#include <gtest/gtest.h>

#include <Core/GameWorld.hpp>
#include <Features/HunterUnit.hpp>

using namespace sw;

TEST(UnitAttackCloseTest, UnitAttackFalse) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t healthInit = 5;
    std::shared_ptr<IUnit> unit(new HunterUnit(world, 0, 3, 2, healthInit, 1));
    world.addUnit(unit);

    auto a = dynamic_cast<IAttackableClose*>(unit.get());
    bool attacked = a->doAttackClose();
    EXPECT_FALSE(attacked);
    
    auto h = dynamic_cast<IHealthable*>(unit.get());
    EXPECT_EQ(h->getHealth(), healthInit);
}

TEST(UnitAttackCloseTest, UnitAttackNearest) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t healthInit = 5;
    std::shared_ptr<IUnit> attacker(new HunterUnit(world, 0, 2, 2, healthInit, 1));
    world.addUnit(attacker);
    std::shared_ptr<IUnit> defender(new HunterUnit(world, 1, 3, 2, healthInit, 1));
    world.addUnit(defender);

    auto a = dynamic_cast<IAttackableClose*>(attacker.get());
    bool attacked = a->doAttackClose();
    EXPECT_TRUE(attacked);

    auto healthAttacker = dynamic_cast<IHealthable*>(attacker.get());
    auto healthDefender = dynamic_cast<IHealthable*>(defender.get());

    EXPECT_EQ(healthAttacker->getHealth(), healthInit);
    EXPECT_EQ(healthDefender->getHealth(), healthInit - 1);
}

TEST(UnitAttackCloseTest, EventUnitAttackNearest) {
    GameWorld world;
    world.createMap(10, 10);
    
    uint32_t attackerId = 0;
    uint32_t attackerStrength = 1;
    uint32_t targetId = 1;
    uint32_t healthInit = 5;
    std::shared_ptr<IUnit> attacker(new HunterUnit(world, attackerId, 2, 2, healthInit, attackerStrength));
    world.addUnit(attacker);
    std::shared_ptr<IUnit> defender(new HunterUnit(world, targetId, 3, 2, healthInit, 1));
    world.addUnit(defender);

    auto a = dynamic_cast<IAttackableClose*>(attacker.get());
    testing::internal::CaptureStdout();
    a->doAttackClose();
    std::string output = testing::internal::GetCapturedStdout();

    std::stringstream expected;
    expected << "[0] UNIT_ATTACKED attackerUnitId=" << attackerId << " targetUnitId=" << targetId <<
        " damage=" << attackerStrength << " targetHp=" << healthInit - 1 << " \n";
    
    EXPECT_EQ(output, expected.str());
}