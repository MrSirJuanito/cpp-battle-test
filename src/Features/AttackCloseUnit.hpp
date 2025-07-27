#pragma once

#include <Core/IAttackableClose.hpp>
#include <IO/Events/UnitAttacked.hpp>

namespace sw {
    class AttackCloseUnit : public virtual IAttackableClose {
        private:
            IUnit& owner;
            uint32_t strength;

        public:
            AttackCloseUnit(IUnit& _owner, uint32_t _strength) :
                owner{_owner},
                strength{_strength}
            {}

            uint32_t getStrength() const override { return strength; }

            bool doAttackClose() override {
                return false;
            }
    };
}