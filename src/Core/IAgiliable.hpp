#pragma once

#include <cstdint>
#include <Core/IUnit.hpp>

namespace sw {
    struct IAgiliable : public virtual IUnit {
        virtual bool doAttackFar() = 0;
        virtual uint32_t getAgility() const = 0;
        virtual uint32_t getRange() const = 0;
        virtual uint32_t getMaxEnemies() const = 0;
    };
}