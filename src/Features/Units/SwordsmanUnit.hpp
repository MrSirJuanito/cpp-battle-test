#pragma once

#include <Core/BaseUnit.hpp>
#include <Features/Behaviors/HealthBehavior.hpp>
#include <Features/Behaviors/MarchBehavior.hpp>
#include <Features/Behaviors/AttackCloseBehavior.hpp>

namespace sw {
	class SwordsmanUnit : public BaseUnit, public HealthBehavior, public MarchBehavior, public AttackCloseBehavior {
	public:
		SwordsmanUnit(IGameWorld& _world, uint32_t _id, uint32_t _x, uint32_t _y, uint32_t _health, uint32_t _strength) : 
			BaseUnit{_world, _id, _x, _y},
			HealthBehavior{*this, _health},
			MarchBehavior{*this, 1},
			AttackCloseBehavior{*this, _strength, 1}
		{}
	
		std::string getTypeName() const override { return "Swordsman"; }
	};
}