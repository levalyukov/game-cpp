#pragma once

#include "pause.hpp"
#include "hud.hpp"
#include "kitchen.hpp"
#include "glocery-shop.hpp"
#include "warehouse.hpp"
#include "orders.hpp"

#include <memory>

class UI {
	public: 
		UI(
			UIManager& ui_manager,
			ResourceManager& resourse_manager,
			CookingManager& cooking_manager,
			EconomyManager& economy_manager,
			GloceryShopManager& glocery_shop_manager,
			WarehouseManager& warehouse_manager,
			OrdersManager& orders_manager
		) : uiManager(ui_manager), 
			resourceManager(resourse_manager),
			cookingManager(cooking_manager),
			economyManager(economy_manager),
			gloceryShopManager(glocery_shop_manager),
			warehouseManager(warehouse_manager),
			ordersManager(orders_manager) { allSetup(); };

		inline void allSetup() {
			pause->setup();
			hud->setup();
			kitchenMenu->setup();
			gloceryShop->setup();
			gloceryShop->setHUD(hud.get());
			warehouse->setup();
			orders->setup();
		};

		inline HUD* getHUD() const { return hud.get(); };
		inline OrdersDisplay* getOrderDisplay() const { return orders.get(); };

		~UI() { pause = nullptr; hud = nullptr; kitchenMenu = nullptr; gloceryShop = nullptr; };

	private:
		Globals& globals = Globals::instance();
		UIManager& uiManager;
		ResourceManager& resourceManager;
		EconomyManager& economyManager;
		CookingManager& cookingManager;
		GloceryShopManager& gloceryShopManager;
		WarehouseManager& warehouseManager;
		OrdersManager& ordersManager;

		std::unique_ptr<GloceryShop> gloceryShop = std::make_unique<GloceryShop>(uiManager, resourceManager, economyManager, gloceryShopManager, warehouseManager, globals);
		std::unique_ptr<Pause> pause = std::make_unique<Pause>(uiManager, resourceManager, globals);
		std::unique_ptr<HUD> hud = std::make_unique<HUD>(uiManager, resourceManager, economyManager, *gloceryShop, globals);
		std::unique_ptr<KitchenMenu> kitchenMenu = std::make_unique<KitchenMenu>(uiManager, resourceManager, cookingManager, globals);
		std::unique_ptr<Warehouse> warehouse = std::make_unique<Warehouse>(uiManager, resourceManager, warehouseManager, globals);
		std::unique_ptr<OrdersDisplay> orders = std::make_unique<OrdersDisplay>(uiManager, resourceManager, ordersManager);
};