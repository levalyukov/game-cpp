#pragma once

#include "../ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/economy-manager.hpp"
#include "glocery-shop.hpp"

class HUD {
	public:
		HUD(
			UIManager& ui_manager,
			ResourceManager& resource_manager,
			EconomyManager& economy_manager,
			GloceryShop& glocery_shop_ui
		) : uiManager(ui_manager), 
			resourceManager(resource_manager),
			economyManager(economy_manager),
			gloceryShopUI(glocery_shop_ui) {};

		void setup();
		void update();

	private:
		UIManager& uiManager;
		ResourceManager& resourceManager;
		EconomyManager& economyManager;
		GloceryShop& gloceryShopUI;

		bool visible = true;

		void initResources();
		void initElements();
		void initLayers();
		void initParameters();
};