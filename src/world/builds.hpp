#pragma once

#include "../core/resources/resources.hpp"
#include "../ui/ui-manager.hpp"
#include "../ui/screens/inventory.hpp"
#include "../entities/entity-manager.hpp"
#include "../entities/entities/build.hpp"
#include "../mechanics/cooking-manager.hpp"
#include "../mechanics/inventory-manager.hpp"

#define DISTANCE_FOR_INTERACTION 125

class Builds {
	public:
		inline void create(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			UIManager& uiManager,
			CookingManager& cookingManager,
			InventoryManager& inventoryManager,
			Inventory& inventory_ui,
			Globals& global_manager
		) {
			initResources(resourceManager);
			initBuilds(entityManager, resourceManager, uiManager, cookingManager, inventoryManager);
			initParameters(entityManager, resourceManager, uiManager, cookingManager, inventoryManager, inventory_ui, global_manager);
		};

	private:
		inline void initResources(ResourceManager& resourceManager) {
			resourceManager.loadTexture("kitchen", "../../../assets/textures/entity/builds/kitchen/kitchen.png");
			resourceManager.loadTexture("warehouse", "../../../assets/textures/entity/builds/warehouse/warehouse.png");
		};

		inline void initBuilds(
			EntityManager& entityManager, 
			ResourceManager& resourceManager, 
			UIManager& uiManager, 
			CookingManager& cookingManager,
			InventoryManager& inventoryManager
		) {
			entityManager.addEntity("kitchen", std::make_unique<Build>(resourceManager.getTexture("kitchen"), sf::Vector2f({ 512.f,512.f }), sf::Vector2i({ 16,16 })));
			entityManager.addEntity("warehouse", std::make_unique<Build>(resourceManager.getTexture("warehouse"), sf::Vector2f({ 640.f,640.f }), sf::Vector2i({ 16,16 })));
		};

		inline void initParameters(
			EntityManager& entityManager,
			ResourceManager& resourceManager,
			UIManager& uiManager,
			CookingManager& cookingManager,
			InventoryManager& inventoryManager,
			Inventory& inventory_ui,
			Globals& global_manager
		) {
			initKitchen(entityManager, uiManager, cookingManager, inventoryManager, inventory_ui, global_manager);
			initWarehouse(entityManager, uiManager, global_manager);
		};

		inline void initKitchen(
			EntityManager& entityManager,
			UIManager& uiManager, 
			CookingManager& cookingManager,
			InventoryManager& inventoryManager,
			Inventory& inventory_ui,
			Globals& global_manager
		) {
			auto kitchen = static_cast<Build*>(entityManager.getEntity("kitchen"));
			kitchen->setHandler(
				[&]() {
					if (global_manager.getUIOpened()) return;

					auto player = static_cast<Player*>(entityManager.getEntity("player"));
					auto build = static_cast<Build*>(entityManager.getEntity("kitchen"));
					if (entityManager.getDistance(build->getSprite(), player->getSprite()) <= DISTANCE_FOR_INTERACTION) {
						if (!cookingManager.getCookeedFlag() && !cookingManager.getCookingFlag()) {
							global_manager.setUIOpened(true);
							uiManager.getElement("kitchen-ui-background")->setVisible(true);
							uiManager.getElement("kitchen-ui-panel")->setVisible(true);
							uiManager.getElement("kitchen-ui-close-button")->setVisible(true);
							for (int y = 0; y < cookingManager.recipes.size(); y++) {
								std::string buttonRecipe = "kitchen-ui-recipe-button-" + std::to_string(y);
								std::string buttonLabelRecipe = "kitchen-ui-recipe-button-" + std::to_string(y) + "-label";
								if (uiManager.getElement(buttonRecipe) && uiManager.getElement(buttonLabelRecipe)) {
									uiManager.getElement(buttonRecipe)->setVisible(true);
									uiManager.getElement(buttonLabelRecipe)->setVisible(true);
								};
							};
						} else if (cookingManager.getCookeedFlag()) {
							if (inventoryManager.inventory.size() < MAX_INVENTORY_SLOTS) {
								cookingManager.resetCookeedFlag();
								inventoryManager.addItem("bread", { "Bread", "../../../assets/textures/ui/inventory/items/item_0.png" });
								inventory_ui.update();
							};
						};
					};
				}
			);
		};

		inline void initWarehouse(
			EntityManager& entityManager,
			UIManager& uiManager,
			Globals& global_manager
		) {
			auto warehouse = static_cast<Build*>(entityManager.getEntity("warehouse"));
			warehouse->setHandler(
				[&]() {
					if (global_manager.getUIOpened()) return;

					auto player = static_cast<Player*>(entityManager.getEntity("player"));
					auto build = static_cast<Build*>(entityManager.getEntity("warehouse"));
					if (entityManager.getDistance(build->getSprite(), player->getSprite()) <= DISTANCE_FOR_INTERACTION) {
						if (!uiManager.getElement("warehouse-background")) return;
						if (!uiManager.getElement("warehouse-panel")) return;

						global_manager.setUIOpened(true);
						uiManager.getElement("warehouse-background")->setVisible(true);
						uiManager.getElement("warehouse-panel")->setVisible(true);
						uiManager.getElement("warehouse-close-button")->setVisible(true);
					};
				}
			);
		};
};