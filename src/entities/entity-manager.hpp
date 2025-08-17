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
			auto result = entities.emplace(name, std::move(entity));
			if (result.second) {
				renderEntities.push_back(result.first->second.get());
			}
		};

		inline Entity* getEntity(std::string enitityName) {
			std::transform(enitityName.begin(), enitityName.end(), enitityName.begin(), [](unsigned char c) {return std::tolower(c); });
			auto entity = entities.find(enitityName);
			return (entity != entities.end()) ? entity->second.get() : nullptr;
		};

		inline void removeEntity(std::string enitityName) { 
			std::transform(enitityName.begin(), enitityName.end(), enitityName.begin(), [](unsigned char c) {return std::tolower(c); });
			auto entity = entities.find(enitityName);
			auto it = std::find(renderEntities.begin(), renderEntities.end(), entity->second.get());
			if (it != renderEntities.end()) renderEntities.erase(it);
			if (entity != entities.end()) entities.erase(enitityName);
		};
		
		inline void render(float deltaTime, sf::View& game_camera) {
			if (entities.empty()) return;

			std::sort(renderEntities.begin(), renderEntities.end(), [](Entity* a, Entity* b) {
				return a->getDepth() < b->getDepth();
			});

			for (auto& object : renderEntities) {
				object->render(globals.getWindow(), deltaTime, game_camera, globals.getClock());
				object->handleEvent(globals.getWindow(), globals.getEvent());
			}
		};

	private:
		std::vector <Entity*> renderEntities;
		std::map <std::string, std::unique_ptr<Entity>> entities;
		Globals& globals = Globals::instance();
}; 