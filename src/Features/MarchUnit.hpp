#pragma once

#include <Core/IGameWorld.hpp>
#include <Core/BaseUnit.hpp>
#include <Core/IMarchable.hpp>

namespace sw {
    class MarchUnit : public IMarchable, public BaseUnit {
        private:
            IGameWorld& world;
            uint32_t speed;
            uint32_t targetX;
            uint32_t targetY;

        public:
            MarchUnit(IGameWorld& _world, uint32_t _id, uint32_t _x, uint32_t _y, uint32_t _speed) :
                BaseUnit{_id, _x, _y},
                world{_world},
                speed{_speed},
                targetX{_x},
                targetY{_y}
            {}

            void marchTo(uint32_t _targetX, uint32_t _targetY) override {
                targetX = _targetX;
                targetY = _targetY;
                world.getEventLog().log(world.getTick(), io::MarchStarted{id, x, y, targetX, targetY});
            }

            void doMarch() override{
                if (targetX == x && targetY == y) {
                    return;
                }

                int dx = (targetX > x) ? 1 : (targetX < x) ? -1 : 0;
                int dy = (targetY > y) ? 1 : (targetY < y) ? -1 : 0;      
                x += dx;
                y += dy;

                world.getEventLog().log(world.getTick(), io::UnitMoved{id, x, y});

                if (x == targetX && y == targetY)
                    world.getEventLog().log(world.getTick(), io::MarchEnded{id, x, y});
            }

            uint32_t getTargetX() const override { return targetX; }
            uint32_t getTargetY() const override { return targetY; }
    };
}