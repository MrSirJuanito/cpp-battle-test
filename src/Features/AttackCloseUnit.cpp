#include "AttackCloseUnit.hpp"
#include <vector>
#include <memory>
#include <Core/IHealthable.hpp>
#include <IO/Events/UnitAttacked.hpp>

namespace sw {
    bool AttackCloseUnit::doAttackClose() {
        std::vector<std::shared_ptr<IUnit>> unitsAttack;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                // Skip checking for target at your own position
                if (dx == 0 && dy == 0)
                    continue;
                
                // Check the world dimensions
                if (static_cast<int>(owner.getX()) + dx < 0 ||
                    static_cast<int>(owner.getX()) + dx >= owner.getWorld().getWidth() ||
                    static_cast<int>(owner.getY()) + dy < 0 ||
                    static_cast<int>(owner.getY()) + dy >= owner.getWorld().getHeight())
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

            uint32_t healthNew = (h->getHealth() >= strength ) ? h->getHealth() - strength : 0;

            owner.getWorld().getEventLog().log(owner.getWorld().getTick(), 
                io::UnitAttacked{owner.getId(), unitsAttack[attackId]->getId(), strength, healthNew});
            
            h->setHealth(healthNew);

            unitsAttack.erase(unitsAttack.begin() + attackId);
            attackedSomebody = true;
        }

        return attackedSomebody;
    }
}