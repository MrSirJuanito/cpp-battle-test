#pragma once

#include <cmath>
#include <Core/Interfaces/IUnit.hpp>

namespace sw {
    struct Utils {
        static uint32_t distanceTo(IUnit& orig, uint32_t targetX, uint32_t targetY) {
                return static_cast<uint32_t>(std::sqrt(
                    std::pow(static_cast<double>(orig.getX()) - static_cast<double>(targetX), 2) +
                    std::pow(static_cast<double>(orig.getY()) - static_cast<double>(targetY), 2))
                );
            }
    };
}