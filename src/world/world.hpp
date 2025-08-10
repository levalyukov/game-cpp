#pragma once

#include "characters.hpp"
#include "../entities/entity-manager.hpp"
#include "../core/resources/resources.hpp"

class World {
	public:
		World() {
			characters.spawn(resourceManager, entityManager);
		};

		inline void render(float delta, sf::View& game_camera) {
			entityManager.render(delta, game_camera);
		};

	private:
		ResourceManager& resourceManager = ResourceManager::instance();
		EntityManager& entityManager = EntityManager::instance();
		Characters& characters = Characters::instance();
};