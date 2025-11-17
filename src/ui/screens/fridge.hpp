#pragma once

#include "../../core/globals.hpp"
#include "../ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/fridge-manager.hpp"

class Fridge {
	public:
		Fridge(
			UIManager& ui_manager,
			ResourceManager& resource_manager,
			FridgeManager& fridge_manager,
			Globals& global_manager
		) : uiManager(ui_manager),
			resourceManager(resource_manager),
			fridgeManager(fridge_manager),
			globals(global_manager) {}

		void setup();
		void update();
		void setVisible(bool new_state);

	private:
		Globals& globals;
		UIManager& uiManager;
		ResourceManager& resourceManager;
		FridgeManager& fridgeManager;

		bool visible = false;

		const size_t SORT_INDEX_BACKGROUND = 8;
		const size_t SORT_INDEX_PANEL = 9;
		const size_t SORT_INDEX_BUTTON = 10;

		void initResources();
		void initElements();
		void initLayers();
		void initParameters();
};