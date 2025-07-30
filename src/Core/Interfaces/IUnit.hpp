#pragma once

#include <cstdint>
#include <string>
#include <Core/Interfaces/IGameWorld.hpp>

namespace sw {
    struct IUnit {
        virtual ~IUnit() = default;
		virtual std::string getTypeName() const = 0;
        virtual IGameWorld& getWorld() = 0;
        virtual uint32_t getId() const = 0;
		virtual uint32_t getX() const = 0;
		virtual uint32_t getY() const = 0;
        virtual void setX(uint32_t _x) = 0;
		virtual void setY(uint32_t _y) = 0;
    };
}