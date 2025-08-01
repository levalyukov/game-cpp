#pragma once

#include "entity.hpp"

#include <map>

class EntityManager {
	public:
		inline static EntityManager& Instance() {
			static EntityManager r;
			return r;
		}

		inline void addEntity(std::string name, std::unique_ptr<Entity> entity) { 
			entities.emplace(name, std::move(entity));
		};

		inline Entity* getEntity(std::string enitityName) {
			auto entity = entities.find(enitityName);
			return (entity != entities.end()) ? entity->second.get() : nullptr;
		};

		inline void removeEntity(std::string enitityName) { 
			if (entities.find(enitityName) != entities.end()) entities.erase(enitityName);
		};
		
		inline void render(sf::RenderWindow& window, float deltaTime, sf::View& gameCamera, sf::Event& event, sf::Clock& clock) {
			if (entities.empty()) return;
			for (auto& object : entities) {
				object.second->render(window, deltaTime, gameCamera, clock);
				object.second->handleEvent(window, event);
			}
		};

	private:
		std::map <std::string, std::unique_ptr<Entity>> entities;

		EntityManager() {};
		~EntityManager() {};
		EntityManager(EntityManager& const) = delete;
		EntityManager& operator=(EntityManager& const) = delete;
}; 