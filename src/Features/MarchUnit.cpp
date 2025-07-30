#include "MarchUnit.hpp"
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/MarchEnded.hpp>

namespace sw {
    void MarchUnit::marchTo(uint32_t _targetX, uint32_t _targetY) {
        if (_targetX >= owner.getWorld().getWidth() || _targetY >= owner.getWorld().getHeight())
            throw new std::runtime_error("March destination is beyond the map!");

        targetX = _targetX;
        targetY = _targetY;
        owner.getWorld().getEventLog().log(owner.getWorld().getTick(), 
            io::MarchStarted{owner.getId(), owner.getX(), owner.getY(), targetX, targetY});
    }

    bool MarchUnit::doMarch() {
        if (targetX == owner.getX() && targetY == owner.getY()) {
            return false;
        }

        uint32_t newX = (targetX > owner.getX()) ? owner.getX() + 1 : 
            (targetX < owner.getX()) ? owner.getX() - 1 : owner.getX();
        uint32_t newY = (targetY > owner.getY()) ? owner.getY() + 1 : 
            (targetY < owner.getY()) ? owner.getY() - 1 : owner.getY();     
        owner.setX(newX);
        owner.setY(newY);

        owner.getWorld().getEventLog().log(owner.getWorld().getTick(), 
            io::UnitMoved{owner.getId(), owner.getX(), owner.getY()});

        if (owner.getX() == targetX && owner.getY() == targetY) {
            owner.getWorld().getEventLog().log(owner.getWorld().getTick(),
                io::MarchEnded{owner.getId(), owner.getX(), owner.getY()});
            return false;
        }

        return true;
    }
}