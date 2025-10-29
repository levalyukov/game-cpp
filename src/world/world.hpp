#pragma once

#include "../entities/entity-manager.hpp"
#include "../core/resources/resources.hpp"
#include "../mechanics/event-manager.hpp"
#include "../mechanics/orders-manager.hpp"
#include "../ui/screens/ui.hpp"

#include "characters.hpp"
#include "nature.hpp"
#include "builds.hpp"

class World {
	public:
		World(
			UIManager& ui_manager,
			EntityManager& entity_manager,
			ResourceManager& resource_manager,
			CookingManager& cooking_manager,
			EconomyManager& economy_manager,
			EventManager& event_manager,
			OrdersManager& order_manager,
			Items& items_container,
			UI& main_ui
		) : uiManager(ui_manager),
			entityManager(entity_manager),
			resourceManager(resource_manager),
			cookingManager(cooking_manager),
			economyManager(economy_manager),
			eventManager(event_manager),
			orderManager(order_manager),
			items(items_container),
			ui(main_ui) {
			characters->spawn(resourceManager, entityManager, economyManager, *ui.getHUD());
			builds->create(resourceManager, entityManager, uiManager, cookingManager, orderManager, *ui.getOrderDisplay(), items_container);
			//eventManager.addEvent("passerby", { [&]() {characters->passerby(resourceManager, entityManager); }, 12.25f, true });
			//eventManager.addEvent("customer", { [&]() {characters->customer(resourceManager, entityManager, orderManager, eventManager, *ui.getOrderDisplay(), items); }, 1.5f, !true });
			orderManager.addOrder("test-1", { 1, items.getRecipeInfo(1)->title, items.getRecipeInfo(1)->cook_time, items.getRecipeInfo(1)->icon_path, 100});
			ui.getOrderDisplay()->update();
		};

		inline void render(float delta, sf::View& game_camera) {
			entityManager.render(delta, game_camera);
			cookingManager.cookingProcess(delta);
			eventManager.update(delta);
		};

		~World() { characters = nullptr; nature = nullptr; builds = nullptr; };

	private:
		UI& ui;
		Items& items;
		UIManager& uiManager;
		EntityManager& entityManager;
		ResourceManager& resourceManager;
		CookingManager& cookingManager;
		EconomyManager& economyManager;
		EventManager& eventManager;
		OrdersManager& orderManager;

		std::unique_ptr<Characters> characters = std::make_unique<Characters>();
		std::unique_ptr<Nature> nature = std::make_unique<Nature>();
		std::unique_ptr<Builds> builds = std::make_unique<Builds>();
};