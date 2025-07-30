#pragma once

#include <Core/Interfaces/IAgiliable.hpp>

namespace sw {
    class AttackFarBehavior : public virtual IAgiliable {
        private:
            IUnit& owner;
            uint32_t agility;
            uint32_t range;
            uint32_t maxEnemies;

        public:
            AttackFarBehavior(IUnit& _owner, uint32_t _agility, uint32_t _range, uint32_t _maxEnemies) :
                owner{_owner},
                agility{_agility},
                range{_range},
                maxEnemies{_maxEnemies}
            {}

            uint32_t getAgility() const override { return agility; }
            uint32_t getRange() const override { return range; }
            uint32_t getMaxEnemies() const override { return maxEnemies; }

            bool doAttackFar() override;
    };
}