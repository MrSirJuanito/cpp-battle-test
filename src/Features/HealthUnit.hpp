#pragma once

#include <Core/IHealthable.hpp>

namespace sw {
    class HealthUnit : public virtual IHealthable {
        private:
            IUnit& owner;
            uint32_t health;

        public:
            HealthUnit(IUnit& _owner, uint32_t _health) :
                owner{_owner},
                health{_health}
            {}

            uint32_t getHealth() const override { return health; }
            void setHealth(uint32_t _health) override { health = _health; }
    };
}