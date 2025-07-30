#include <gtest/gtest.h>

#include <fstream>
#include <IO/System/CommandParser.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <Core/GameWorld.hpp>
#include <Features/SwordsmanUnit.hpp>
#include <Features/HunterUnit.hpp>
#include <Core/IMarchable.hpp>

using namespace sw;

class CommandParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        parser.add<io::CreateMap>([&](auto command) {
            world.createMap(command.width, command.height);
        })
	    .add<io::SpawnSwordsman>([&](auto command) {
            world.addUnit(std::shared_ptr<IUnit>(new SwordsmanUnit(world, command.unitId, command.x, command.y, command.hp, command.strength)));
        })
	    .add<io::SpawnHunter>([&](auto command) {
            world.addUnit(std::shared_ptr<IUnit>(new HunterUnit(world, command.unitId, command.x, command.y, command.hp, command.agility, command.strength, command.range)));
        })
	    .add<io::March>([&](auto command) {
            std::shared_ptr<IUnit>& unit = world.getUnitById(command.unitId);
            auto m = dynamic_cast<IMarchable*>(unit.get());
            m->marchTo(command.targetX, command.targetY);
        });
    }

    GameWorld world;
    io::CommandParser parser;
};

TEST_F(CommandParserTest, CommandExists) {
    EXPECT_ANY_THROW(parser.add<io::CreateMap>([](auto command) {}));
}

TEST_F(CommandParserTest, ParseCreateMapCommand) {
    std::stringstream file;
    file << "CREATE_MAP 10 10";

    testing::internal::CaptureStdout();
    parser.parse(file);
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(world.getWidth(), 10);
    EXPECT_EQ(world.getHeight(), 10);
}

TEST_F(CommandParserTest, ParseSpawnSwordsmanCommand) {
    std::stringstream file;
    file << "SPAWN_SWORDSMAN 1 0 0 5 2";

    testing::internal::CaptureStdout();
    parser.parse(file);
    testing::internal::GetCapturedStdout();

    std::shared_ptr<IUnit>& unit = world.getUnitById(1);
    EXPECT_EQ(unit->getId(), 1);
    EXPECT_EQ(unit->getTypeName(), "Swordsman");
    EXPECT_EQ(unit->getX(), 0);
    EXPECT_EQ(unit->getY(), 0);
}

TEST_F(CommandParserTest, ParseSpawnHunterCommand) {
    std::stringstream file;
    file << "SPAWN_HUNTER 2 9 0 10 5 1 4";

    testing::internal::CaptureStdout();
    parser.parse(file);
    testing::internal::GetCapturedStdout();

    std::shared_ptr<IUnit>& unit = world.getUnitById(2);
    EXPECT_EQ(unit->getId(), 2);
    EXPECT_EQ(unit->getTypeName(), "Hunter");
    EXPECT_EQ(unit->getX(), 9);
    EXPECT_EQ(unit->getY(), 0);

    auto h = dynamic_cast<IHealthable*>(unit.get());
    EXPECT_EQ(h->getHealth(), 10);

    auto s = dynamic_cast<IStrengthable*>(unit.get());
    EXPECT_EQ(s->getStrength(), 1);

    auto a = dynamic_cast<IAgiliable*>(unit.get());
    EXPECT_EQ(a->getAgility(), 5);
    EXPECT_EQ(a->getRange(), 4);
}

TEST_F(CommandParserTest, EventParseCreateMapCommand) {
    std::stringstream file;
    file << "CREATE_MAP 10 10";

    testing::internal::CaptureStdout();
    parser.parse(file);
    std::string output = testing::internal::GetCapturedStdout();

    std::string expected = "[1] MAP_CREATED width=10 height=10 \n";
    EXPECT_EQ(output, expected);
}

TEST_F(CommandParserTest, EventParseSpawnSwordsmanCommand) {
    std::stringstream file;
    file << "SPAWN_SWORDSMAN 1 0 0 5 2";

    testing::internal::CaptureStdout();
    parser.parse(file);
    std::string output = testing::internal::GetCapturedStdout();

    std::string expected = "[1] UNIT_SPAWNED unitId=1 unitType=Swordsman x=0 y=0 \n";
    EXPECT_EQ(output, expected);
}

TEST_F(CommandParserTest, EventParseSpawnHunterCommand) {
    std::stringstream file;
    file << "SPAWN_HUNTER 2 9 0 10 5 1 4";

    testing::internal::CaptureStdout();
    parser.parse(file);
    std::string output = testing::internal::GetCapturedStdout();

    std::string expected = "[1] UNIT_SPAWNED unitId=2 unitType=Hunter x=9 y=0 \n";
    EXPECT_EQ(output, expected);
}

TEST_F(CommandParserTest, ParseFile) {
    std::ifstream file("commands_example.txt");

    testing::internal::CaptureStdout();
    parser.parse(file);
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(world.getWidth(), 10);
    EXPECT_EQ(world.getHeight(), 10);

    std::shared_ptr<IUnit>& unit = world.getUnitById(1);
    EXPECT_EQ(unit->getId(), 1);
    EXPECT_EQ(unit->getTypeName(), "Swordsman");
    EXPECT_EQ(unit->getX(), 0);
    EXPECT_EQ(unit->getY(), 0);

    unit = world.getUnitById(2);
    EXPECT_EQ(unit->getId(), 2);
    EXPECT_EQ(unit->getTypeName(), "Hunter");
    EXPECT_EQ(unit->getX(), 9);
    EXPECT_EQ(unit->getY(), 0);

    unit = world.getUnitById(3);
    EXPECT_EQ(unit->getId(), 3);
    EXPECT_EQ(unit->getTypeName(), "Swordsman");
    EXPECT_EQ(unit->getX(), 0);
    EXPECT_EQ(unit->getY(), 9);
}

TEST_F(CommandParserTest, EventParseFile) {
    std::ifstream file("commands_example.txt");

    testing::internal::CaptureStdout();
    parser.parse(file);
    std::string output = testing::internal::GetCapturedStdout();

    std::string expected = 
        "[1] MAP_CREATED width=10 height=10 \n"\
        "[1] UNIT_SPAWNED unitId=1 unitType=Swordsman x=0 y=0 \n"\
        "[1] UNIT_SPAWNED unitId=2 unitType=Hunter x=9 y=0 \n"\
        "[1] MARCH_STARTED unitId=1 x=0 y=0 targetX=9 targetY=0 \n"\
        "[1] MARCH_STARTED unitId=2 x=9 y=0 targetX=0 targetY=0 \n"\
        "[1] UNIT_SPAWNED unitId=3 unitType=Swordsman x=0 y=9 \n"\
        "[1] MARCH_STARTED unitId=3 x=0 y=9 targetX=0 targetY=0 \n";
    EXPECT_EQ(output, expected);
}