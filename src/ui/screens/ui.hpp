#pragma once

#include "pause.hpp"
#include "hud.hpp"
#include "kitchen.hpp"
#include "inventory.hpp"
#include "glocery-shop.hpp"
#include "warehouse.hpp"

class UI {
	public: 
		UI(
			UIManager& ui_manager,
			ResourceManager& resourse_manager,
			CookingManager& cooking_manager,
			InventoryManager& inventory_manager,
			EconomyManager& economy_manager,
			GloceryShopManager& glocery_shop_manager,
			WarehouseManager& warehouse_manager
		) : uiManager(ui_manager), 
			resourceManager(resourse_manager),
			cookingManager(cooking_manager),
			inventoryManager(inventory_manager),
			economyManager(economy_manager),
			gloceryShopManager(glocery_shop_manager),
			warehouseManager(warehouse_manager) { allSetup(); };

		inline void allSetup() {
			pause->setup();
			hud->setup();
			kitchenMenu->setup();
			inventory->setup();
			gloceryShop->setup();
			gloceryShop->setHUD(hud.get());
			warehouse->setup();
		};

		inline Inventory* getInventory() const { return inventory.get(); };
		inline HUD* getHUD() const { return hud.get(); };

		~UI() { pause = nullptr; hud = nullptr; kitchenMenu = nullptr; inventory = nullptr; gloceryShop = nullptr; };

	private:
		Globals& globals = Globals::instance();
		UIManager& uiManager;
		ResourceManager& resourceManager;
		EconomyManager& economyManager;
		InventoryManager& inventoryManager;
		CookingManager& cookingManager;
		GloceryShopManager& gloceryShopManager;
		WarehouseManager& warehouseManager;

		std::unique_ptr<GloceryShop> gloceryShop = std::make_unique<GloceryShop>(uiManager, resourceManager, economyManager, gloceryShopManager, warehouseManager, globals);
		std::unique_ptr<Pause> pause = std::make_unique<Pause>(uiManager, resourceManager, globals);
		std::unique_ptr<HUD> hud = std::make_unique<HUD>(uiManager, resourceManager, economyManager, *gloceryShop, globals);
		std::unique_ptr<KitchenMenu> kitchenMenu = std::make_unique<KitchenMenu>(uiManager, resourceManager, cookingManager, globals);
		std::unique_ptr<Inventory> inventory = std::make_unique<Inventory>(uiManager, resourceManager, inventoryManager);
		std::unique_ptr<Warehouse> warehouse = std::make_unique<Warehouse>(uiManager, resourceManager, warehouseManager, globals);
};