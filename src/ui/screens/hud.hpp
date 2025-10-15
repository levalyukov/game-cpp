#pragma once

#include "../ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/economy-manager.hpp"
#include "glocery-shop.hpp"
#include "IHUD.h"

class HUD : public IHUD {
	public:
		HUD(
			UIManager& ui_manager,
			ResourceManager& resource_manager,
			EconomyManager& economy_manager,
			GloceryShop& glocery_ui,
			Globals& global_manager
		) : uiManager(ui_manager), 
			resourceManager(resource_manager),
			economyManager(economy_manager),
			gloceryShop(glocery_ui),
			globals(global_manager) {};

		void setup();
		void update() override;

	private:
		Globals& globals;
		UIManager& uiManager;
		ResourceManager& resourceManager;
		EconomyManager& economyManager;
		GloceryShop& gloceryShop;

		const size_t SORT_INDEX_MONEY = 4;
		const size_t SORT_INDEX_GLOCERY = 0;
		bool visible = true;

		void initResources();
		void initElements();
		void initLayers();
		void initParameters();
};