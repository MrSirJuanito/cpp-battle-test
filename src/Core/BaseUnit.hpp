#pragma once

#include <cstdint>
#include <string>
#include <iostream>

class BaseUnit {
    friend class GameMap;
private:
    uint32_t id;
    uint32_t x;
    uint32_t y;

public:
    BaseUnit() {
        std::cout << "B " << std::endl;
    }

    BaseUnit(uint32_t x, uint32_t y) :
        x{x}, y{y} {
        std::cout << "Bxy " << std::endl;
    }

    uint32_t getId() const {
        return id;
    }

    virtual ~BaseUnit() = default;

protected:
    void setId(uint32_t id) {
        id = id;
    }
};