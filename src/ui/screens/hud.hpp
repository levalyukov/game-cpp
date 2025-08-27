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
		inline void setVisible(bool _state) { visible = _state; changeElementVisible(); };
		inline bool getVisible() const { return visible; };
		inline void changeElementVisible() {
			if (uiManager.getElement("hud-button")) {
				uiManager.getElement("hud-button")->setVisible(visible);
			}
		};

	private:
		UIManager& uiManager;
		ResourceManager& resourceManager;

		bool visible = true;

		void initResources();
		void initElements();
		void initLayers();
};