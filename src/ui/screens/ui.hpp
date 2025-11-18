#pragma once

#include "screen.hpp"
#include "pause.hpp"
#include "hud.hpp"
#include "bake.hpp"
#include "glocery-shop.hpp"
#include "fridge.hpp"
#include "orders.hpp"

#include <memory>
#include <vector>

class UI {
	public: 
		UI(
			UIManager& ui_manager,
			ResourceManager& resourse_manager,
			CookingManager& cooking_manager,
			EconomyManager& economy_manager,
			GloceryShopManager& glocery_shop_manager,
			FridgeManager& fridge_manager,
			OrdersManager& orders_manager
		) : uiManager(ui_manager), 
			resourceManager(resourse_manager),
			cookingManager(cooking_manager),
			economyManager(economy_manager),
			gloceryShopManager(glocery_shop_manager),
			fridgeManager(fridge_manager),
			ordersManager(orders_manager) { 
			screens.emplace_back(pause);
			screens.emplace_back(kitchenMenu);
			screens.emplace_back(fridge);
			screens.emplace_back(orders);
			allSetup(); 
		};
		std::vector<std::shared_ptr<Screen>> screens;
		inline void allSetup() {
			for (auto& screen : screens) {
				if (screen) screen->setup();
			};
			hud->setup();
			gloceryShop->setHUD(hud.get());
			gloceryShop->setup();
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
		FridgeManager& fridgeManager;
		OrdersManager& ordersManager;

		std::unique_ptr<GloceryShop> gloceryShop = std::make_unique<GloceryShop>(uiManager, resourceManager, economyManager, gloceryShopManager, fridgeManager, globals);
		std::shared_ptr<Pause> pause = std::make_unique<Pause>(uiManager, resourceManager, globals);
		std::unique_ptr<HUD> hud = std::make_unique<HUD>(uiManager, resourceManager, economyManager, *gloceryShop, globals);
		std::shared_ptr<BakeMenu> kitchenMenu = std::make_unique<BakeMenu>(uiManager, resourceManager, cookingManager, globals);
		std::shared_ptr<Fridge> fridge = std::make_unique<Fridge>(uiManager, resourceManager, fridgeManager, globals);
		std::shared_ptr<OrdersDisplay> orders = std::make_unique<OrdersDisplay>(uiManager, resourceManager, ordersManager);
};