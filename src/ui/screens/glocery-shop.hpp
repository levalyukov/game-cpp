#pragma once

#include "IHUD.h"
#include "../ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/glocery-shop-manager.hpp"
#include "../../mechanics/economy-manager.hpp"
#include "../../mechanics/warehouse-manager.hpp"

class GloceryShop {
	public:
		GloceryShop(
			UIManager& ui_manager,
			ResourceManager& resource_manager,
			EconomyManager& economy_manager,
			GloceryShopManager& glocery_shop_manager,
			WarehouseManager& warehouse_manager,
			Globals& global_manager
		) : resourceManager(resource_manager),
			uiManager(ui_manager),
			economyManager(economy_manager),
			gloceryShopManager(glocery_shop_manager),
			warehouseManager(warehouse_manager),
			globals(global_manager) {};

		void setup();
		void update();
		void setVisible(bool new_state);
		inline bool getVisible() const { return visible; };
		inline void setHUD(IHUD* hud_ref) { hud = hud_ref; };

	private:
		Globals& globals;
		IHUD* hud = nullptr;
		UIManager& uiManager;
		ResourceManager& resourceManager;
		EconomyManager& economyManager;
		GloceryShopManager& gloceryShopManager;
		WarehouseManager& warehouseManager;

		bool visible = true;
		unsigned int page = 1;
		unsigned int maxPages = 0;

		const size_t SORT_INDEX_BACKGROUND = 4;
		const size_t SORT_INDEX_PANEL = 5;
		const size_t SORT_INDEX_BUTTON = 6;
		const size_t SORT_INDEX_TEXT = 7;

		void initResources();
		void initElements();
		void initLayers();
		void initParametes();
		void initButtons();
};