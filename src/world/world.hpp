#pragma once

#include "../entities/entity-manager.hpp"
#include "../core/resources/resources.hpp"

#include "characters.hpp"
#include "nature.hpp"
#include "builds.hpp"

class World {
	public:
		World(
			UIManager& ui_manager,
			EntityManager& entity_manager,
			ResourceManager& resource_manager,
			CookingManager& cooking_manager
		) : uiManager(ui_manager),
			entityManager(entity_manager),
			resourceManager(resource_manager),
			cookingManager(cooking_manager) {
			characters->spawn(resourceManager, entityManager);
			builds->create(resourceManager, entityManager, uiManager, cookingManager);
		};
		
		~World() {
			characters = nullptr;
			nature = nullptr;
			builds = nullptr;
		}

		inline void render(float delta, sf::View& game_camera) {
			entityManager.render(delta, game_camera);
		};

	private:
		UIManager& uiManager;
		EntityManager& entityManager;
		ResourceManager& resourceManager;
		CookingManager& cookingManager;

		std::unique_ptr<Characters> characters = std::make_unique<Characters>();
		std::unique_ptr<Nature> nature = std::make_unique<Nature>();
		std::unique_ptr<Builds> builds = std::make_unique<Builds>();
};