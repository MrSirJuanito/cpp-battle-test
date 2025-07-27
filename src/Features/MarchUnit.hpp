#pragma once

#include <Core/IGameWorld.hpp>
#include <Core/IMarchable.hpp>

namespace sw {
    class MarchUnit : public virtual IMarchable {
        private:
            IUnit& owner;
            uint32_t speed;
            uint32_t targetX;
            uint32_t targetY;

        public:
            MarchUnit(IUnit& _owner, uint32_t _speed) :
                owner{_owner},
                speed{_speed}
            {}

            void marchTo(uint32_t _targetX, uint32_t _targetY) override {
                targetX = _targetX;
                targetY = _targetY;
                owner.getWorld().getEventLog().log(owner.getWorld().getTick(), 
                    io::MarchStarted{owner.getId(), owner.getX(), owner.getY(), targetX, targetY});
            }

            void doMarch() override {
                if (targetX == owner.getX() && targetY == owner.getY()) {
                    return;
                }

                int dx = (targetX > owner.getX()) ? 1 : (targetX < owner.getX()) ? -1 : 0;
                int dy = (targetY > owner.getY()) ? 1 : (targetY < owner.getY()) ? -1 : 0;      
                owner.setX(owner.getX() + dx);
                owner.setY(owner.getY() + dy);

                owner.getWorld().getEventLog().log(owner.getWorld().getTick(), 
                    io::UnitMoved{owner.getId(), owner.getX(), owner.getY()});

                if (owner.getX() == targetX && owner.getY() == targetY)
                    owner.getWorld().getEventLog().log(owner.getWorld().getTick(),
                        io::MarchEnded{owner.getId(), owner.getX(), owner.getY()});
            }

            uint32_t getTargetX() const override { return targetX; }
            uint32_t getTargetY() const override { return targetY; }
    };
}