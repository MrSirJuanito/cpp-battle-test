#pragma once

#include <Core/BaseUnit.hpp>
#include <Features/HealthUnit.hpp>
#include <Features/MarchUnit.hpp>
#include <Features/AttackCloseUnit.hpp>

namespace sw {
	class SwordsmanUnit : public BaseUnit, public HealthUnit, public MarchUnit, public AttackCloseUnit {
	public:
		SwordsmanUnit(IGameWorld& _world, uint32_t _id, uint32_t _x, uint32_t _y, uint32_t _health, uint32_t _strength) : 
			BaseUnit{_world, _id, _x, _y},
			HealthUnit{*this, _health},
			MarchUnit{*this, 1},
			AttackCloseUnit{*this, _strength, 1}
		{}
	
		std::string getTypeName() const override { return "Swordsman"; }
	};
}