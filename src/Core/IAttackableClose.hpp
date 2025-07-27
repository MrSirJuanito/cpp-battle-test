#pragma once

#include <cstdint>
#include <Core/IUnit.hpp>

namespace sw {
    struct IAttackableClose : public virtual IUnit {
        virtual bool doAttackClose() = 0;
        virtual uint32_t getStrength() const = 0;
    };
}