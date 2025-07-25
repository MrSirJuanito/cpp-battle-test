#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <unordered_map>
#include <Core/BaseUnit.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/Events/UnitSpawned.hpp>

namespace sw {
	class GameMap {
	private:
		EventLog eventLog;
	
		uint32_t width;
		uint32_t height;
		std::unordered_map<uint32_t, std::unique_ptr<BaseUnit>> units;
		uint32_t currentMove;
	
	public:
		GameMap(uint32_t width, uint32_t height) : width{width}, height{height} {
			currentMove = 0;
		}
	
		uint32_t addUnit(std::unique_ptr<BaseUnit>& unit) {
			uint32_t id = units.size();
			unit->setId(id);
	
			eventLog.log(currentMove, io::UnitSpawned{id, unit->getTypeName(), unit->getX(), unit->getY()});
	
			units[id] = std::move(unit);
	
			return id;
		}
	
		std::unique_ptr<BaseUnit>& getUnit(uint32_t id) {
			if (units.count(id) == 0)
				throw new std::exception();
			return units.at(id);
		}
	};
}