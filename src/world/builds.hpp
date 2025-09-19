#pragma once

#include "../ui/ui-manager.hpp"
#include "../core/resources/resources.hpp"
#include "../entities/entity-manager.hpp"
#include "../mechanics/cooking.hpp"
#include "../entities/entities/build.hpp"
#include "../mechanics/inventory-manager.hpp"
#include "../ui/screens/inventory.hpp"

class Builds {
	public:
		inline void create(
			ResourceManager& resource_manager,
			EntityManager& entity_manager,
			UIManager& ui_manager,
			CookingManager& cooking_manager,
			InventoryManager& inventory_manager,
			Inventory& inventory_ui
		) {
			initResources(resource_manager);
			initBuilds(
				entity_manager, 
				resource_manager, 
				ui_manager, 
				cooking_manager,
				inventory_manager,
				inventory_ui
			);
		};

	private:
		inline void initResources(ResourceManager& resource_manager) {
			resource_manager.loadTexture("kitchen", "../../../assets/textures/entity/builds/kitchen/kitchen.png");
		};

		inline void initBuilds(
			EntityManager& entity_manager, 
			ResourceManager& resource_manager, 
			UIManager& ui_manager, 
			CookingManager& cooking_manager,
			InventoryManager& inventory_manager,
			Inventory& inventory_ui
		) {
			entity_manager.addEntity(
				"kitchen",
				std::make_unique<Build>(
					resource_manager.getTexture("kitchen"),
					sf::Vector2f({ 512.f,512.f }),
					sf::Vector2i({ 16,16 })
				)
			);
			initKitchen(
				entity_manager, 
				ui_manager, 
				cooking_manager,
				inventory_manager,
				inventory_ui
			);
		};

		inline void initKitchen(
			EntityManager& entity_manager,
			UIManager& ui_manager, 
			CookingManager& cooking_manager,
			InventoryManager& inventory_manager,
			Inventory& inventory_ui
		) {
			auto kitchen = static_cast<Build*>(entity_manager.getEntity("kitchen"));
			kitchen->setHandleEvent(
				[&]() {
					if (!cooking_manager.getCookeedFlag() && !cooking_manager.getCookingFlag()) {
						ui_manager.getElement("kitchen-ui-background")->setVisible(true);
						ui_manager.getElement("kitchen-ui-panel")->setVisible(true);
						ui_manager.getElement("kitchen-ui-close-button")->setVisible(true);
						for (int y = 0; y < cooking_manager.recipes.size(); y++) {
							std::string buttonRecipe = "kitchen-ui-recipe-button-" + std::to_string(y);
							std::string buttonLabelRecipe = "kitchen-ui-recipe-button-" + std::to_string(y) + "-label";
							if (ui_manager.getElement(buttonRecipe) && ui_manager.getElement(buttonLabelRecipe)) {
								ui_manager.getElement(buttonRecipe)->setVisible(true);
								ui_manager.getElement(buttonLabelRecipe)->setVisible(true);
							}
						}
					}
					else {
						if (inventory_manager.inventory.size() < inventory_manager.MAX_SLOTS) {
							cooking_manager.resetCookeedFlag();
							inventory_manager.addItem("bread", { "Bread", "../../../assets/textures/ui/inventory/items/item_0.png" });
							inventory_ui.update();
						}
					}
				}
			);
		};
};