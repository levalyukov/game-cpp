#pragma once

#include "../ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/economy-manager.hpp"

class HUD {
	public:
		HUD(
			UIManager& ui_manager,
			ResourceManager& resource_manager,
			EconomyManager& economy_manager
		) : uiManager(ui_manager), 
			resourceManager(resource_manager),
			economyManager(economy_manager) {};

		void setup();
		void update();

	private:
		UIManager& uiManager;
		ResourceManager& resourceManager;
		EconomyManager& economyManager;

		bool visible = true;

		void initResources();
		void initElements();
		void initLayers();
};