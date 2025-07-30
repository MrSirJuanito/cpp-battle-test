#pragma once

#include <Core/Interfaces/IHealthable.hpp>
#include <IO/Events/UnitDied.hpp>

namespace sw {
    class HealthBehavior : public virtual IHealthable {
        private:
            IUnit& owner;
            uint32_t health;

        public:
            HealthBehavior(IUnit& _owner, uint32_t _health) :
                owner{_owner},
                health{_health}
            {}

            uint32_t getHealth() const override { return health; }
            void setHealth(uint32_t _health) override {
                health = _health;

                // Only emit the event, the actual clean up happens in the game world class at the end of a tick
                if (health == 0) {
                    owner.getWorld().getEventLog().log(owner.getWorld().getTick(), 
                        io::UnitDied{owner.getId()});
                }
            }
    };
}