#pragma once

#include <Core/IUnit.hpp>

namespace sw {
	class BaseUnit : public IUnit {
	protected:
		uint32_t id;
		uint32_t x;
		uint32_t y;
	
	public:
		BaseUnit(uint32_t _x, uint32_t _y) : 
			x{_x},
			y{_y} 
		{}
	
		uint32_t getId() const override { return id; }
		uint32_t getX() const override { return x; }
		uint32_t getY() const override { return y; }

		void setId(uint32_t _id) { id = _id; }
	};
}