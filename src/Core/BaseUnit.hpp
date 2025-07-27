#pragma once

#include <Core/IUnit.hpp>

namespace sw {
	class BaseUnit : public virtual IUnit {
	protected:
		IGameWorld& world;
		uint32_t id;
		uint32_t x;
		uint32_t y;
	
	public:
		BaseUnit(IGameWorld& _world, uint32_t _id, uint32_t _x, uint32_t _y) : 
			world{_world},
			id{_id},
			x{_x},
			y{_y} 
		{}
	
		IGameWorld& getWorld() override { return world; }
		uint32_t getId() const override { return id; }
		uint32_t getX() const override { return x; }
		uint32_t getY() const override { return y; }
		void setX(uint32_t _x) override { x = _x; }
		void setY(uint32_t _y) override { y = _y; }
	};
}