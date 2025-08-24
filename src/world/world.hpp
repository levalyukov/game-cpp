#pragma once

#include "../entities/entity-manager.hpp"
#include "../core/resources/resources.hpp"

#include "characters.hpp"
#include "nature.hpp"
#include "builds.hpp"

class World {
	public:
		World() {
			characters.spawn(resourceManager, entityManager);
			builds.create(resourceManager, entityManager);
		};

		inline void render(float delta, sf::View& game_camera) {
			entityManager.render(delta, game_camera);
		};

	private:
		ResourceManager& resourceManager = ResourceManager::instance();
		EntityManager& entityManager = EntityManager::instance();
		Characters& characters = Characters::instance();
		Nature& nature = Nature::instance();
		Builds& builds = Builds::instance();
};