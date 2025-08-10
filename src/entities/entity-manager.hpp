#pragma once

#include "entity.hpp"

#include <map>
#include <string>
#include <cctype>
#include <algorithm>

class EntityManager {
	public:
		EntityManager() {};
		~EntityManager() {};
		EntityManager(EntityManager& const) = delete;
		EntityManager& operator=(EntityManager& const) = delete;
		inline static EntityManager& instance() {
			static EntityManager r;
			return r;
		}

		inline void addEntity(std::string name, std::unique_ptr<Entity> entity) { 
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {return std::tolower(c); });
			entities.emplace(name, std::move(entity));
		};

		inline Entity* getEntity(std::string enitityName) {
			std::transform(enitityName.begin(), enitityName.end(), enitityName.begin(), [](unsigned char c) {return std::tolower(c); });
			auto entity = entities.find(enitityName);
			return (entity != entities.end()) ? entity->second.get() : nullptr;
		};

		inline void removeEntity(std::string enitityName) { 
			std::transform(enitityName.begin(), enitityName.end(), enitityName.begin(), [](unsigned char c) {return std::tolower(c); });
			if (entities.find(enitityName) != entities.end()) entities.erase(enitityName);
		};
		
		inline void render(float deltaTime, sf::View& game_camera) {
			if (entities.empty()) return;
			for (auto& object : entities) {
				object.second->render(globals.getWindow(), deltaTime, game_camera, globals.getClock());
				object.second->handleEvent(globals.getWindow(), globals.getEvent());
			}
		};

	protected:
		std::map <std::string, std::unique_ptr<Entity>> entities;
		Globals& globals = Globals::instance();
}; 