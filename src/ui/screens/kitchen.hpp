#pragma once

#include "../../core/globals.hpp"
#include "../../core/utils.hpp"
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
		Utils& utils = Utils::instance();
		Globals& globals = Globals::instance();
		sf::RenderWindow& window = globals.getWindow();
		ResourceManager& resourceManager;
		UIManager& uiManager;
		CookingManager& cooking;

		bool visibleState = false;
		std::string currentRecipe;

		void initResources();
		void initElements();
		void initParameters();

		void initPanel();
		void initCloseButton();
		void initRecipeButtons();
		void initRecipeInfo();

		void setVisible(bool _state);
		void getRecipeInfo(std::string recipe_name);
};