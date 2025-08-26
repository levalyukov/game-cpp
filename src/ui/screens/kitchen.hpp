#pragma once

#include "../../core/globals.hpp"
#include "../../ui/ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../screens/hud.hpp"
#include "../../mechanics/cooking.hpp"

#include <iostream>

class KitchenMenu {
	public:
		KitchenMenu() {};
		~KitchenMenu() {};
		KitchenMenu(KitchenMenu& const) = delete;
		KitchenMenu& operator=(KitchenMenu& const) = delete;
		inline static KitchenMenu& instance() {
			static KitchenMenu km;
			return km;
		}

		void setup();
		inline bool getVisible() const { return visible; };
		inline void setVisible(bool _state) { visible = _state; changeElementVisible(); };
		inline void changeElementVisible() {
			uiManager.getElement("kitchen-ui-background")->setVisible(visible);
			uiManager.getElement("kitchen-ui-panel")->setVisible(visible);
			uiManager.getElement("kitchen-ui-close-button")->setVisible(visible);
			button_cout = cooking.recipes.size();
			for (int y = 0; y < button_cout; y++) {
				std::string buttonName = "kitchen-ui-recipe-button-" + std::to_string(y);
				if (uiManager.getElement(buttonName)) {
					uiManager.getElement(buttonName)->setVisible(visible);
				}
			}
		};

	private:
		bool visible = false;
		unsigned int button_cout = 0;

		void initResources();
		void initElements();
		void initVisible();
		void initLambdas();

		Globals& globals = Globals::instance();
		sf::RenderWindow& window = globals.getWindow();
		ResourceManager& resourceManager = ResourceManager::instance();
		UIManager& uiManager = UIManager::instance();
		Cooking& cooking = Cooking::instance();
};