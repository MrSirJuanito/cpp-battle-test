#pragma once

#include <Core/Interfaces/IStrengthable.hpp>

namespace sw {
    class AttackCloseBehavior : public virtual IStrengthable {
        private:
            IUnit& owner;
            uint32_t strength;
            uint32_t maxEnemies;

        public:
            AttackCloseBehavior(IUnit& _owner, uint32_t _strength, uint32_t _maxEnemies) :
                owner{_owner},
                strength{_strength},
                maxEnemies{_maxEnemies}
            {}

            uint32_t getStrength() const override { return strength; }
            uint32_t getMaxEnemies() const override { return maxEnemies; }

            bool doAttackClose() override;
    };
}