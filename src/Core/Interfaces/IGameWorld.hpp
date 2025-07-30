#pragma once

#include <cstdint>
#include <memory>
#include <IO/System/EventLog.hpp>

namespace sw {
    class IUnit;
    struct IGameWorld {
        virtual ~IGameWorld() = default;
        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        virtual uint32_t getNextId() const = 0;
        virtual EventLog& getEventLog() = 0;
        virtual uint64_t getTick() const = 0;

        virtual bool existUnitAtPos(uint32_t _x, uint32_t _y) = 0;
        virtual std::shared_ptr<IUnit>& getUnitAtPos(uint32_t _x, uint32_t _y) = 0;
        virtual std::shared_ptr<IUnit>& getUnitById(uint32_t _id) = 0;
    };
}