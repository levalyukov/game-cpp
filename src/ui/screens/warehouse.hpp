#pragma once

#include "../../core/globals.hpp"
#include "../ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/warehouse-manager.hpp"

class Warehouse {
	public:
		Warehouse(
			UIManager& ui_manager,
			ResourceManager& resource_manager,
			WarehouseManager& warehouse_manager,
			Globals& global_manager
		) : uiManager(ui_manager),
			resourceManager(resource_manager),
			warehouseManager(warehouse_manager),
			globals(global_manager) {}

		void setup();
		void update();
		void setVisible(bool new_state);

	private:
		Globals& globals;
		UIManager& uiManager;
		ResourceManager& resourceManager;
		WarehouseManager& warehouseManager;

		bool visible = false;

		const unsigned int SORT_INDEX_BACKGROUND = 8;
		const unsigned int SORT_INDEX_PANEL = 9;
		const unsigned int SORT_INDEX_BUTTON = 10;

		void initResources();
		void initElements();
		void initLayers();
		void initParameters();
};