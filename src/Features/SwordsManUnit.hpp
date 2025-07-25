#pragma once

#include <Core/BaseUnit.hpp>

namespace sw {
	class SwordsManUnit : public BaseUnit {
	public:
		SwordsManUnit(uint32_t x, uint32_t y) : BaseUnit(x, y) {}
	
		std::string getTypeName() const override { return "Swordsman"; }
	};
}