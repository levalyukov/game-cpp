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

	private:
		Globals& globals = Globals::instance();
		sf::RenderWindow& window = globals.getWindow();
		ResourceManager& resourceManager;
		UIManager& uiManager;
		CookingManager& cooking;

		void initResources();
		void initElements();
		void initParameters();
		void initVisible();
		
		void initPanel();
		void initCloseButton();
		void initRecipeButtons();
		void initRecipeInfo();

};