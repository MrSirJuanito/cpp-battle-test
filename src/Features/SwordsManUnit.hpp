#pragma once

#include <Core/BaseUnit.hpp>
#include <Features/MarchUnit.hpp>
#include <Features/AttackCloseUnit.hpp>

namespace sw {
	class SwordsManUnit : public BaseUnit, public MarchUnit, public AttackCloseUnit {
	public:
		SwordsManUnit(IGameWorld& _world, uint32_t _id, uint32_t _x, uint32_t _y, uint32_t _strength) : 
			BaseUnit{_world, _id, _x, _y},
			MarchUnit{*this, 1},
			AttackCloseUnit{*this, _strength}
		{}
	
		std::string getTypeName() const override { return "Swordsman"; }
	};
}