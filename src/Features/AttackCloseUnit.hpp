#pragma once

#include <vector>
#include <memory>
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
                std::vector<std::shared_ptr<IUnit>> unitsAttack;

                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (dx == 0 && dy == 0)
                            continue;
                         
                        if (owner.getWorld().existUnitAtPos(owner.getX() + dx, owner.getY() + dy)) {
                            std::shared_ptr<IUnit>& unit = owner.getWorld().getUnitAtPos(owner.getX() + dx, owner.getY() + dy);
                            // Attach only those units that are Healthable (have HP)
                            if (auto h = dynamic_cast<IHealthable*>(unit.get())) {
                                unitsAttack.push_back(unit);
                            }
                        }
                    }
                }

                if (unitsAttack.size() == 0)
                    return false;
                
                uint32_t attackId = rand() % unitsAttack.size();
                auto h = dynamic_cast<IHealthable*>(unitsAttack[attackId].get());
                h->setHealth(h->getHealth() - strength);
                return true;
            }
    };
}