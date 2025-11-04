#pragma once

#include "../screens/hud.hpp"
#include "../../core/globals.hpp"
#include "../../ui/ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../../mechanics/cooking-manager.hpp"

#include <string>
#include <iostream>

class KitchenMenu {
	public:
		KitchenMenu(
			UIManager& ui_manager,
			ResourceManager& resource_manager, 
			CookingManager& cooking_manager,
			Globals& global_manager
		) : uiManager(ui_manager), 
			resourceManager(resource_manager),
			cooking(cooking_manager),
			globals(global_manager) {};

		void setup();

	private:
		Globals& globals;
		sf::RenderWindow& window = globals.getWindow();
		ResourceManager& resourceManager;
		UIManager& uiManager;
		CookingManager& cooking;

		std::string currentRecipe;
		bool visible = false;

		const size_t SORT_INDEX_BACKGROUND = 0;
		const size_t SORT_INDEX_PANEL = 1;
		const size_t SORT_INDEX_BUTTON = 2;
		const size_t SORT_INDEX_TEXT = 3;

		void initResources();
		void initElements();
		void initParameters();

		void initCloseButton();
		void initRecipeButtons();
		void initRecipeInfo();

		void setVisible(bool _state);
		void getRecipeInfo(std::string recipe_name);
};