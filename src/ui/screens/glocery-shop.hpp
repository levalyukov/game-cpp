#pragma once

#include "../ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/glocery-shop-manager.hpp"

class GloceryShop {
	public:
		GloceryShop(
			UIManager& ui_manager,
			ResourceManager& resource_manager,
			GloceryShopManager& glocery_shop_manager
		) : resourceManager(resource_manager),
			uiManager(ui_manager),
			gloceryShopManager(glocery_shop_manager) {};

		void setup();
		void update();
		void setVisible(bool new_state);
		inline bool getVisible() const { return visible; };

	private:
		UIManager& uiManager;
		ResourceManager& resourceManager;
		GloceryShopManager& gloceryShopManager;

		bool visible = true;
		unsigned int page = 1;
		unsigned int maxPages = 0;

		const unsigned int SORT_INDEX_BACKGROUND = 4;
		const unsigned int SORT_INDEX_PANEL = 5;
		const unsigned int SORT_INDEX_BUTTON = 6;
		const unsigned int SORT_INDEX_TEXT = 7;

		void initResources();
		void initElements();
		void initLayers();
		void initParametes();
		void initButtons();
};