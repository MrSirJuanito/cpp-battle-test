#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <unordered_map>
#include <Core/BaseUnit.hpp>

class GameMap {
private:
    uint32_t width;
    uint32_t height;
    std::unordered_map<uint32_t, std::unique_ptr<BaseUnit>> units;

public:
    GameMap(uint32_t width, uint32_t height) : width{width}, height{height} {}

    uint32_t addUnit(std::unique_ptr<BaseUnit>& unit) {
        uint32_t id = units.size();
        unit->setId(id);
        units[id] = std::move(unit);
        return id;
    }

    std::unique_ptr<BaseUnit>& getUnit(uint32_t id) {
        if (units.count(id) == 0)
            throw new std::exception();
        return units.at(id);
    }
};