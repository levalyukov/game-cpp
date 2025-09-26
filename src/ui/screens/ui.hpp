#pragma once

#include "pause.hpp"
#include "hud.hpp"
#include "kitchen.hpp"
#include "inventory.hpp"

class UI {
	/* for init only */
	public: 
		UI(
			UIManager& ui_manager,
			ResourceManager& resourse_manager,
			CookingManager& cooking_manager,
			InventoryManager& inventory_manager,
			EconomyManager& economy_manager
		) : uiManager(ui_manager), 
			resourceManager(resourse_manager),
			cookingManager(cooking_manager),
			inventoryManager(inventory_manager),
			economyManager(economy_manager) { allSetup(); };

		inline void allSetup() {
			pause->setup();
			hud->setup();
			kitchenMenu->setup();
			inventory->setup();
		};

		inline Inventory* getInventory() const { return inventory.get(); };
		inline HUD* getHUD() const { return hud.get(); };

		~UI() {
			pause = nullptr;
			hud = nullptr;
			kitchenMenu = nullptr;
			inventory = nullptr;
		}

	private:
		UIManager& uiManager;
		ResourceManager& resourceManager;
		CookingManager& cookingManager;
		InventoryManager& inventoryManager;
		EconomyManager& economyManager;

		std::unique_ptr<Pause> pause = std::make_unique<Pause>(uiManager, resourceManager);
		std::unique_ptr<HUD> hud = std::make_unique<HUD>(uiManager, resourceManager, economyManager);
		std::unique_ptr<KitchenMenu> kitchenMenu = std::make_unique<KitchenMenu>(uiManager, resourceManager, cookingManager);
		std::unique_ptr<Inventory> inventory = std::make_unique<Inventory>(uiManager, resourceManager, inventoryManager);
};