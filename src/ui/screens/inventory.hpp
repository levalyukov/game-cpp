#pragma once

#include "../../ui/ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/inventory-manager.hpp"

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

		void initResources();
		void initElements();
		void initParameters();
};