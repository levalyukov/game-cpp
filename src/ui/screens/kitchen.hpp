#pragma once

#include "../screens/hud.hpp"
#include "../../core/globals.hpp"
#include "../../ui/ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/cooking-manager.hpp"

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

		const unsigned int SORT_INDEX_BACKGROUND = 0;
		const unsigned int SORT_INDEX_PANEL = 1;
		const unsigned int SORT_INDEX_BUTTON = 2;
		const unsigned int SORT_INDEX_TEXT = 3;

		bool visibleState = false;
		std::string currentRecipe;

		void initResources();
		void initElements();
		void initParameters();

		void initCloseButton();
		void initRecipeButtons();
		void initRecipeInfo();

		void setVisible(bool _state);
		void getRecipeInfo(std::string recipe_name);
};