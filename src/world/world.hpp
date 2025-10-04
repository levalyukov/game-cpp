#pragma once

#include "../entities/entity-manager.hpp"
#include "../core/resources/resources.hpp"
#include "../mechanics/inventory-manager.hpp"
#include "../ui/screens/inventory.hpp"

#include "characters.hpp"
#include "nature.hpp"
#include "builds.hpp"

class World {
	public:
		World(
			UIManager& ui_manager,
			EntityManager& entity_manager,
			ResourceManager& resource_manager,
			CookingManager& cooking_manager,
			InventoryManager& inventory_manager,
			EconomyManager& economy_manager,
			Inventory& inventory_ui,
			HUD& hud_ui,
			Globals& global_manager
		) : uiManager(ui_manager),
			entityManager(entity_manager),
			resourceManager(resource_manager),
			cookingManager(cooking_manager),
			inventoryManager(inventory_manager),
			economyManager(economy_manager),
			inventoryUI(inventory_ui),
			globals(global_manager) {
			characters->spawn(resourceManager, entityManager, inventoryManager, economyManager, inventoryUI, hud_ui);
			builds->create(resourceManager, entityManager, uiManager, cookingManager, inventoryManager, inventoryUI, global_manager);
		};
		
		~World() {
			characters = nullptr;
			nature = nullptr;
			builds = nullptr;
		}

		inline void render(float delta, sf::View& game_camera) {
			entityManager.render(delta, game_camera);
			cookingManager.cookingProcess(delta);
		};

	private:
		Globals& globals;
		UIManager& uiManager;
		EntityManager& entityManager;
		ResourceManager& resourceManager;
		CookingManager& cookingManager;
		InventoryManager& inventoryManager;
		EconomyManager& economyManager;
		Inventory& inventoryUI;

		std::unique_ptr<Characters> characters = std::make_unique<Characters>();
		std::unique_ptr<Nature> nature = std::make_unique<Nature>();
		std::unique_ptr<Builds> builds = std::make_unique<Builds>();
};