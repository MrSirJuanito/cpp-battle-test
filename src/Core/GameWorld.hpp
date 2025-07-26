#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <unordered_map>
#include <Core/IGameWorld.hpp>
#include <Core/BaseUnit.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <Features/MarchUnit.hpp>

namespace sw {
	class GameWorld : public IGameWorld {
	private:
		EventLog eventLog;
		std::unordered_map<uint32_t, std::shared_ptr<IUnit>> units;

		uint32_t width = 0;
		uint32_t height = 0;
		uint64_t tick = 0;
	
	public:
		uint32_t getWidth() const override { return width; };
        uint32_t getHeight() const override { return height; };
		uint32_t getNextId() const override { return units.size(); }
		EventLog& getEventLog() override { return eventLog; }
		uint64_t getTick() const override { return tick; }

		void createMap(uint32_t _width, uint32_t _height) {
			width = _width;
			height = _height;
			eventLog.log(tick, io::MapCreated{width, height});
		}

		void addUnit(std::shared_ptr<IUnit> unit) {
			uint32_t position = unit->getY() * width + unit->getX();
			if (units.count(position) > 0)
				throw new std::exception();

			eventLog.log(tick, io::UnitSpawned{unit->getId(), unit->getTypeName(), unit->getX(), unit->getY()});
            
			units[position] = std::move(unit);
		}
	
		std::shared_ptr<IUnit>& getUnit(uint32_t id) {
            for (auto& [k, v] : units) {
                if (v->getId() == id)
                    return v;
            }
            // No unit with the given id found
			throw new std::exception();
		}

        uint64_t nextTick() {
			++tick;
            for (auto& [k, v] : units) {
                if (auto m = dynamic_cast<IMarchable*>(v.get())) {
                    m->doMarch();
                }
            }
			return tick;
        }
	};
}