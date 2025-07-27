#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <Core/IGameWorld.hpp>
#include <Core/IUnit.hpp>
#include <Core/IAttackableClose.hpp>
#include <Core/IMarchable.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/MarchEnded.hpp>

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
			uint32_t position = positionAtMap(unit->getX(), unit->getY());
			if (units.count(position) > 0)
				throw new std::runtime_error("Unit at this position already exists");
			
			for (auto& [k, v] : units) {
                if (v->getId() == unit->getId())
                    throw new std::runtime_error("Unit with this id already exists");
            }

			eventLog.log(tick, io::UnitSpawned{unit->getId(), unit->getTypeName(), unit->getX(), unit->getY()});
            
			units[position] = std::move(unit);
		}
	
		bool existUnitAtPos(uint32_t _x, uint32_t _y) override {
			uint32_t position = positionAtMap(_x, _y);
			return units.count(position) > 0;
		}

        std::shared_ptr<IUnit>& getUnitAtPos(uint32_t _x, uint32_t _y) override {
			uint32_t position = positionAtMap(_x, _y);
			return units.at(position);
		}

		std::shared_ptr<IUnit>& getUnitById(uint32_t id) override {
            for (auto& [k, v] : units) {
                if (v->getId() == id)
                    return v;
            }
            // No unit with the given id found
			throw new std::runtime_error("No unit exists with given id");
		}

        uint64_t nextTick() {
			++tick;
            for (auto& [k, v] : units) {
				bool attacked = false;
				if (auto a = dynamic_cast<IAttackableClose*>(v.get())) {
					attacked = a->doAttackClose();
				}
				// If a unit is not attackable or the attack didn't succeed - march
                if (!attacked) 
					if (auto m = dynamic_cast<IMarchable*>(v.get())) {
                    	m->doMarch();
					}
            }
			return tick;
        }

	private:
		uint32_t positionAtMap(uint32_t _x, uint32_t _y) {
			return _y * width + _x;
		}
	};
}