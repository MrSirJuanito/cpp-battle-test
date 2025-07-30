#pragma once

#include <Core/Interfaces/IUnit.hpp>

namespace sw {
    struct IHealthable : public virtual IUnit {
        virtual uint32_t getHealth() const = 0;
        virtual void setHealth(uint32_t _health) = 0;
    };
}