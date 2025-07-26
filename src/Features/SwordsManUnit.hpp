#pragma once

#include <Features/MarchUnit.hpp>

namespace sw {
	class SwordsManUnit : public MarchUnit {
	public:
		SwordsManUnit(IGameWorld& _world, uint32_t _id, uint32_t _x, uint32_t _y) : 
			MarchUnit{_world, _id, _x, _y, 1}
		{}
	
		std::string getTypeName() const override { return "Swordsman"; }
	};
}