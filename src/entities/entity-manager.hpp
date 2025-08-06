#pragma once

#include "entity.hpp"

#include <map>
#include <string>
#include <cctype>
#include <algorithm>

class EntityManager {
	public:
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