#pragma once

#include <cstdint>
#include <IO/System/EventLog.hpp>

namespace sw {
    struct IGameWorld {
        virtual ~IGameWorld() = default;
        virtual uint32_t getNextId() = 0;
        virtual EventLog& getEventLog() = 0;
        virtual uint64_t getTick() const = 0;
    };
}