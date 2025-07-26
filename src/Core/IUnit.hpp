#pragma once

#include <cstdint>
#include <string>

namespace sw {
    struct IUnit {
        virtual ~IUnit() = default;
		virtual std::string getTypeName() const = 0;
        virtual uint32_t getId() const = 0;
		virtual uint32_t getX() const = 0;
		virtual uint32_t getY() const = 0;
    };
}