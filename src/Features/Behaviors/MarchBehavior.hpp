#pragma once

#include <Core/Interfaces/IGameWorld.hpp>
#include <Core/Interfaces/IMarchable.hpp>

namespace sw {
    class MarchBehavior : public virtual IMarchable {
        private:
            IUnit& owner;
            uint32_t speed;
            uint32_t targetX;
            uint32_t targetY;

        public:
            MarchBehavior(IUnit& _owner, uint32_t _speed) :
                owner{_owner},
                speed{_speed}
            {}

            void marchTo(uint32_t _targetX, uint32_t _targetY) override;
            bool doMarch() override;

            uint32_t getTargetX() const override { return targetX; }
            uint32_t getTargetY() const override { return targetY; }
    };
}