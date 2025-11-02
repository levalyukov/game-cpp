#pragma once

#include "entity.hpp"

#include <unordered_map>
#include <string>
#include <cctype>
#include <algorithm>
#include <cmath>

class EntityManager {
	public:
		inline int getDistance(const sf::Sprite first_entity, const sf::Sprite secondary_entity) {
			int firstX = static_cast<int>(first_entity.getPosition().x);
			int firstY = static_cast<int>(first_entity.getPosition().y);
			int secondX = static_cast<int>(secondary_entity.getPosition().x);
			int secondY = static_cast<int>(secondary_entity.getPosition().y);
			int distance = static_cast<int>(std::sqrt(pow(secondX - firstX, 2) + pow(secondY - firstY, 2)));
			return distance;
		};

		inline void addEntity(const std::string entity_name, std::unique_ptr<Entity>&& entity) {
			std::string lower_string = entity_name;
			std::transform(lower_string.begin(), lower_string.end(), lower_string.begin(), 
				[](unsigned char c) {return std::tolower(c); });
			auto result = entities.emplace(lower_string, std::move(entity));
			if (result.second) render_entities.push_back(result.first->second.get());
		};

		inline Entity* getEntity(const std::string entity_name) {
			std::string lower_string = entity_name;
			std::transform(lower_string.begin(), lower_string.end(), lower_string.begin(),
				[](unsigned char c) {return std::tolower(c); });
			auto entity = entities.find(lower_string);
			return (entity != entities.end()) ? entity->second.get() : nullptr;
		};

		inline void removeEntity(const std::string entity_name) {
			std::string lower_string = entity_name;
			std::transform(lower_string.begin(), lower_string.end(), lower_string.begin(), [](unsigned char c) {return std::tolower(c); });
			auto entity = entities.find(lower_string);
			auto it = std::find(render_entities.begin(), render_entities.end(), entity->second.get());
			if (it != render_entities.end()) render_entities.erase(it);
			if (entity != entities.end()) entities.erase(lower_string);
		};
		
		inline void render(const float delta_time, sf::View& game_camera) {
			if (entities.empty()) return;

			std::sort(render_entities.begin(), render_entities.end(), [](Entity* a, Entity* b) {
				return a->getDepth() < b->getDepth();
			});

			for (auto& object : render_entities) {
				object->render(globals.getWindow(), delta_time, game_camera, globals.getClock());
				object->handler(globals.getWindow(), globals.getEvent());
				object->event(globals.getWindow(), globals.getEvent());
			};
		};

	private:
		std::vector<Entity*> render_entities;
		std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
		Globals& globals = Globals::instance();
}; 