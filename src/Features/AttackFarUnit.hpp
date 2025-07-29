#pragma once

#include <vector>
#include <memory>
#include <Core/IAttackableFar.hpp>
#include <Core/IHealthable.hpp>
#include <Core/Utils.hpp>
#include <IO/Events/UnitAttacked.hpp>

namespace sw {
    class AttackFarUnit : public virtual IAttackableFar {
        private:
            IUnit& owner;
            uint32_t agility;
            uint32_t range;
            uint32_t maxEnemies;

        public:
            AttackFarUnit(IUnit& _owner, uint32_t _agility, uint32_t _range, uint32_t _maxEnemies) :
                owner{_owner},
                agility{_agility},
                range{_range},
                maxEnemies{_maxEnemies}
            {}

            uint32_t getAgility() const override { return agility; }
            uint32_t getRange() const override { return range; }
            uint32_t getMaxEnemies() const override { return maxEnemies; }

            bool doAttackFar() override {
                std::vector<std::shared_ptr<IUnit>> unitsAttack;

                for (int dx = -static_cast<int>(range); dx <= static_cast<int>(range); ++dx) {
                    for (int dy = -static_cast<int>(range); dy <= static_cast<int>(range); ++dy) {
                        // Skip checking for target at your own position
                        if (dx == 0 && dy == 0)
                            continue;
                        
                        // Check the world dimensions
                        if (static_cast<int>(owner.getX()) + dx < 0 ||
                            static_cast<int>(owner.getX()) + dx >= owner.getWorld().getWidth() ||
                            static_cast<int>(owner.getY()) + dy < 0 ||
                            static_cast<int>(owner.getY()) + dy >= owner.getWorld().getHeight())
                            continue;

                        uint32_t dist = Utils::distanceTo(owner, owner.getX() + dx, owner.getY() + dy);
                        if (dist > range || dist == 1)
                            continue;
                         
                        if (owner.getWorld().existUnitAtPos(owner.getX() + dx, owner.getY() + dy)) {
                            std::shared_ptr<IUnit>& unit = owner.getWorld().getUnitAtPos(owner.getX() + dx, owner.getY() + dy);
                            // Attach only those units that are Healthable (have HP)
                            if (auto h = dynamic_cast<IHealthable*>(unit.get())) {
                                if (h->getHealth() > 0) {
                                    unitsAttack.emplace_back(unit);
                                }
                            }
                        }
                    }
                }

                // Attacker can be able to attack multiple enemies. Pick each of them randomly
                bool attackedSomebody = false;
                for (uint32_t enemy = 0; enemy < maxEnemies; ++enemy) {
                    if (unitsAttack.size() == 0)
                        continue;
                
                    uint32_t attackId = rand() % unitsAttack.size();
                    auto h = dynamic_cast<IHealthable*>(unitsAttack[attackId].get());

                    uint32_t healthNew = (h->getHealth() >= agility) ? h->getHealth() - agility : 0;
                    
                    owner.getWorld().getEventLog().log(owner.getWorld().getTick(), 
                        io::UnitAttacked{owner.getId(), unitsAttack[attackId]->getId(), agility, healthNew});

                    h->setHealth(healthNew);

                    unitsAttack.erase(unitsAttack.begin() + attackId);
                    attackedSomebody = true;
                }

                return attackedSomebody;
            }
    };
}