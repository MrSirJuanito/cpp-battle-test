#pragma once

#include <cstdint>
#include <IO/System/EventLog.hpp>

namespace sw {
    struct IGameWorld {
        virtual ~IGameWorld() = default;
        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;
        virtual uint32_t getNextId() const = 0;
        virtual EventLog& getEventLog() = 0;
        virtual uint64_t getTick() const = 0;
    };
}