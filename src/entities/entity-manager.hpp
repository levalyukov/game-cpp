#pragma once

#include "entity.hpp"

#include <unordered_map>
#include <string>
#include <cctype>
#include <algorithm>
#include <cmath>

class EntityManager {
	public:
		inline int getDistance(const sf::Sprite first, const sf::Sprite second) {
			int firstX = static_cast<int>(first.getPosition().x);
			int firstY = static_cast<int>(first.getPosition().y);
			int secondX = static_cast<int>(second.getPosition().x);
			int secondY = static_cast<int>(second.getPosition().y);
			int distance = static_cast<int>(std::sqrt(pow(secondX - firstX, 2) + pow(secondY - firstY, 2)));
			return distance;
		};

		inline void addEntity(std::string name, std::unique_ptr<Entity> entity) { 
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {return std::tolower(c); });
			auto result = entities.emplace(name, std::move(entity));
			if (result.second) render_entities.push_back(result.first->second.get());
		};

		inline Entity* getEntity(std::string enitity_name) {
			std::transform(enitity_name.begin(), enitity_name.end(), enitity_name.begin(), [](unsigned char c) {return std::tolower(c); });
			auto entity = entities.find(enitity_name);
			return (entity != entities.end()) ? entity->second.get() : nullptr;
		};

		inline void removeEntity(std::string enitity_name) {
			std::transform(enitity_name.begin(), enitity_name.end(), enitity_name.begin(), [](unsigned char c) {return std::tolower(c); });
			auto entity = entities.find(enitity_name);
			auto it = std::find(render_entities.begin(), render_entities.end(), entity->second.get());
			if (it != render_entities.end()) render_entities.erase(it);
			if (entity != entities.end()) entities.erase(enitity_name);
		};
		
		inline void render(float delta_time, sf::View& game_camera) {
			if (entities.empty()) return;

			std::sort(render_entities.begin(), render_entities.end(), [](Entity* a, Entity* b) {
				return a->getDepth() < b->getDepth();
			});

			for (auto& object : render_entities) {
				object->render(globals.getWindow(), delta_time, game_camera, globals.getClock());
				object->handleEvent(globals.getWindow(), globals.getEvent());
			}
		};

	private:
		std::vector<Entity*> render_entities;
		std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
		Globals& globals = Globals::instance();
}; 