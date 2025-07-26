#pragma once

#include <cstdint>
#include <Core/IUnit.hpp>

namespace sw {
    /*
    enum MarchTypes {
        Begin = 0,
        InProgress = 1,
        End = 2,
        No = 3
    };
    */

    struct IMarchable : public virtual IUnit {
        virtual void marchTo(uint32_t _targetX, uint32_t _targetY) = 0;
        virtual void doMarch() = 0;
        virtual uint32_t getTargetX() const = 0;
        virtual uint32_t getTargetY() const = 0;
    };
}