#pragma once

#include "../ui-manager.hpp"
#include "../../core/resources/resources.hpp"

class HUD {
	public:
		HUD() {};
		~HUD() {};
		HUD(HUD& const) = delete;
		HUD& operator=(HUD& const) = delete;
		inline static HUD& instance() {
			static HUD h;
			return h;
		};

		void setup();
		inline void setVisible(bool _state) { visible = _state; changeElementVisible(); };
		inline bool getVisible() const { return visible; };
		inline void changeElementVisible() {
			if (uiManager.getElement("hud-button")) {
				uiManager.getElement("hud-button")->setVisible(visible);
			}
		};

	private:
		bool visible = true;

		void initResources();
		void initElements();
		void initLayers();

		UIManager& uiManager = UIManager::instance();
		ResourceManager& resourceManager = ResourceManager::instance();
};