#pragma once

#include "../../ui/ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/inventory-manager.hpp"

#include <string>
#include <cctype>
#include <algorithm>

class Inventory {
	public:
		Inventory(
			UIManager& ui_manager,
			ResourceManager& resource_manager,
			InventoryManager& inventory_manager
		) : uiManager(ui_manager),
			resourceManager(resource_manager),
			inventoryManager(inventory_manager) {};

		void setup();
		void update();

	private:
		UIManager& uiManager;
		ResourceManager& resourceManager;
		InventoryManager& inventoryManager;

		const unsigned int SORT_INDEX = -3;
		const unsigned int SORT_INDEX_SLOT = -2;
		const unsigned int SORT_INDEX_SLOT_COUNTER = -1;

		void initResources();
		void initElements();
		void initParameters();
};