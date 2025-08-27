#pragma once

#include "../../core/globals.hpp"
#include "../../ui/ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../screens/hud.hpp"
#include "../../mechanics/cooking.hpp"

#include <iostream>

class KitchenMenu {
	public:
		KitchenMenu(
			UIManager& ui_manager,
			ResourceManager& resource_manager, 
			CookingManager& cooking_manager
		) : uiManager(ui_manager), 
			resourceManager(resource_manager),
			cooking(cooking_manager) {};

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
		Globals& globals = Globals::instance();
		sf::RenderWindow& window = globals.getWindow();
		ResourceManager& resourceManager;
		UIManager& uiManager;
		CookingManager& cooking;

		bool visible = false;
		unsigned int button_cout = 0;

		void initResources();
		void initElements();
		void initVisible();
		void initLambdas();
};