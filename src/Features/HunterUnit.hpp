#pragma once

#include <Core/BaseUnit.hpp>

namespace sw {
	class HunterUnit : public BaseUnit {
	public:
		HunterUnit(uint32_t x, uint32_t y) : BaseUnit(x, y) {}
	
		std::string getTypeName() const override { return "Hunter"; }
	};
}