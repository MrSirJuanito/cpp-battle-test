#include "AttackCloseUnit.hpp"
#include <vector>
#include <memory>
#include <Core/IHealthable.hpp>
#include <IO/Events/UnitAttacked.hpp>

namespace sw {
    bool AttackCloseUnit::doAttackClose() {
        std::vector<std::shared_ptr<IUnit>> unitsAttack;

        uint32_t minX = (owner.getX() > 1) ? owner.getX() - 1 : 0;
        uint32_t minY = (owner.getY() > 1) ? owner.getY() - 1 : 0;

        for (uint32_t x = minX; x <= owner.getX() + 1; ++x) {
            for (uint32_t y = minY; y <= owner.getY() + 1; ++y) {
                // Skip checking for target at your own position
                if (x == owner.getX() && y == owner.getY())
                    continue;
                
                if (owner.getWorld().existUnitAtPos(x, y)) {
                    std::shared_ptr<IUnit>& unit = owner.getWorld().getUnitAtPos(x, y);
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

            uint32_t newHealth = (h->getHealth() >= strength ) ? h->getHealth() - strength : 0;

            owner.getWorld().getEventLog().log(owner.getWorld().getTick(), 
                io::UnitAttacked{owner.getId(), unitsAttack[attackId]->getId(), strength, newHealth});
            
            h->setHealth(newHealth);

            unitsAttack.erase(unitsAttack.begin() + attackId);
            attackedSomebody = true;
        }

        return attackedSomebody;
    }
}