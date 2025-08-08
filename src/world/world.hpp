#pragma once

#include "characters.hpp"
#include "../entities/entity-manager.hpp"
#include "../core/resources/resources.hpp"

class World {
	public:
		World() {
			characters.spawn(resourceManager, entityManager);
		};

		inline void render(sf::RenderWindow& window, sf::Event& event, float delta, sf::View& game_camera, sf::Clock& clock) {
			entityManager.render(window, delta, game_camera, event, clock);
		};

	private:
		ResourceManager& resourceManager = ResourceManager::instance();
		EntityManager& entityManager = EntityManager::instance();
		Characters& characters = Characters::instance();
};