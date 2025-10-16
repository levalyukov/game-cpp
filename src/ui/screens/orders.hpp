#pragma once

#include "../ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/orders-manager.hpp"

class OrdersDisplay {
	public:
		OrdersDisplay(
			UIManager& ui_manager,
			ResourceManager& resource_manager,
			OrdersManager& orders_manager
		) : uiManager(ui_manager),
			resourceManager(resource_manager),
			ordersManager(orders_manager) {};

		void setup();
		void update();

	private:
		UIManager& uiManager;
		ResourceManager& resourceManager;
		OrdersManager& ordersManager;

		const size_t SORT_INDEX_ORDER = 11;
		const size_t SORT_INDEX_ICON = 12;
		const size_t SORT_INDEX_TITLE = 13;
		const size_t SORT_INDEX_PROGRESS_BAR = 14;

		void initResources();
		void initElements();
		void initParameters();
};