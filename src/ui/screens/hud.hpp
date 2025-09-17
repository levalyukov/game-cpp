#pragma once

#include "../ui-manager.hpp"
#include "../../core/resources/resources.hpp"

class HUD {
	public:
		HUD(
			UIManager& ui_manager,
			ResourceManager& resource_manager
		) : uiManager(ui_manager), 
			resourceManager(resource_manager) {};

		void setup();

	private:
		UIManager& uiManager;
		ResourceManager& resourceManager;

		bool visible = true;

		void initResources();
		void initElements();
		void initLayers();
};