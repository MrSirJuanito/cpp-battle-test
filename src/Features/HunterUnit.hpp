#pragma once

#include <Core/BaseUnit.hpp>
#include <Features/HealthUnit.hpp>
#include <Features/MarchUnit.hpp>
#include <Features/AttackCloseUnit.hpp>
#include <Features/AttackFarUnit.hpp>

namespace sw {
	class HunterUnit : public BaseUnit, public HealthUnit, public MarchUnit, public AttackCloseUnit, public AttackFarUnit {
	public:
		HunterUnit(IGameWorld& _world, uint32_t _id, uint32_t _x, uint32_t _y, uint32_t _health, uint32_t _agility, uint32_t _strength, uint32_t _range) :
			BaseUnit{_world, _id, _x, _y},
			HealthUnit{*this, _health},
			MarchUnit{*this, 1},
			AttackCloseUnit{*this, _strength, 1},
			AttackFarUnit{*this, _agility, _range, 1}
		{}
	
		std::string getTypeName() const override { return "Hunter"; }
	};
}