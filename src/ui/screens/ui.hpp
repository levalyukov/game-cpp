#pragma once

#include "pause.hpp"
#include "hud.hpp"
#include "kitchen.hpp"

class UI {
	/* for init only */
	public: 
		UI(
			UIManager& ui_manager,
			ResourceManager& resourse_manager,
			CookingManager& cooking_manager
		) : uiManager(ui_manager), 
			resourceManager(resourse_manager),
			cookingManager(cooking_manager) { allSetup(); };

		inline void allSetup() {
			pause->setup();
			hud->setup();
			kitchenMenu->setup();
		};

	private:
		UIManager& uiManager;
		ResourceManager& resourceManager;
		CookingManager& cookingManager;

		std::unique_ptr<Pause> pause = std::make_unique<Pause>(uiManager, resourceManager);
		std::unique_ptr<HUD> hud = std::make_unique<HUD>(uiManager, resourceManager);
		std::unique_ptr<KitchenMenu> kitchenMenu = std::make_unique<KitchenMenu>(uiManager, resourceManager, cookingManager);
};