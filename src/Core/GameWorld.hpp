#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>
#include <Core/IGameWorld.hpp>
#include <Core/IUnit.hpp>
#include <Core/IHealthable.hpp>
#include <Core/IAttackableClose.hpp>
#include <Core/IAttackableFar.hpp>
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
		std::vector<uint32_t> unitIds;

		uint32_t width = 0;
		uint32_t height = 0;
		uint64_t tick = 1;
	
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
			if (units.count(unit->getId()) > 0)
				throw new std::runtime_error("Unit with this id already exists");
			
			for (auto& [k, v] : units) {
                if (v->getX() == unit->getX() && v->getY() == unit->getY())
                    throw new std::runtime_error("Unit with this id already exists");
            }

			eventLog.log(tick, io::UnitSpawned{unit->getId(), unit->getTypeName(), unit->getX(), unit->getY()});
            
			unitIds.emplace_back(unit->getId());
			units[unit->getId()] = std::move(unit);
		}
	
		bool existUnitAtPos(uint32_t _x, uint32_t _y) override {
			for (auto& [k, v] : units) {
                if (v->getX() == _x && v->getY() == _y)
                    return true;
            }
			return false;
		}

        std::shared_ptr<IUnit>& getUnitAtPos(uint32_t _x, uint32_t _y) override {
			for (auto& [k, v] : units) {
                if (v->getX() == _x && v->getY() == _y)
                    return v;
            }
			// No unit with the given id found
			throw new std::runtime_error("No unit exists at given position");
		}

		std::shared_ptr<IUnit>& getUnitById(uint32_t id) override {
            return units.at(id);
		}

        bool nextTick() {
			++tick;
			bool action = false;
			for (auto& id : unitIds) {
				auto& v = getUnitById(id);
				if (auto h = dynamic_cast<IHealthable*>(v.get())) {
					if (h->getHealth() <= 0)
						continue;
				}

				bool attackedClose = false;
				if (auto a = dynamic_cast<IAttackableClose*>(v.get())) {
					attackedClose = a->doAttackClose();
				}
				// If a unit is not attackable or the attack didn't succeed - march
                if (attackedClose) {
					action = true;
					continue;
				}

				bool attackedFar = false;
				if (auto a = dynamic_cast<IAttackableFar*>(v.get())) {
					attackedFar = a->doAttackFar();
				}
				if (attackedFar) {
					action = true;
					continue;
				}
				
				bool marched = false;
				if (auto m = dynamic_cast<IMarchable*>(v.get())) {
                    marched = m->doMarch();
				}
				if (marched) {
					action = true;
				}
            }

			// Clean up - erase all units with HP <= 0
			auto it = unitIds.begin();
			while (it != unitIds.end()) {
				auto& v = getUnitById(*it);
				auto h = dynamic_cast<IHealthable*>(v.get());
				if (h->getHealth() <= 0) {
					units.erase(*it);
					it = unitIds.erase(it);
				} else {
					++it;
				}
			}

			return action || units.begin() != units.end();
        }
	};
}