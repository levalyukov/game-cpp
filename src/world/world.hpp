#pragma once

#include "../entities/entity-manager.hpp"
#include "../core/resources/resources.hpp"
#include "../mechanics/event-manager.hpp"
#include "../mechanics/orders-manager.hpp"
#include "../ui/screens/ui.hpp"

#include "characters.hpp"
#include "nature.hpp"
#include "builds.hpp"

#define DISTANCE_FOR_INTERACTION 125

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
			characters->spawn(resourceManager, entityManager);
			builds->create(resourceManager, entityManager, uiManager, cookingManager, orderManager, *ui.getOrderDisplay(), items_container);
			eventManager.addEvent("passerby", { [&]() {characters->passerby(resourceManager, entityManager); }, 12.25f, true });
			eventManager.addEvent("customer", { [&]() {characters->customer(resourceManager, entityManager, cookingManager, orderManager, eventManager, *ui.getOrderDisplay(), economyManager, items, *ui.getHUD()); }, 1.5f, true });
			ui.getOrderDisplay()->update();
		};

		inline void render(const float delta, sf::View& camera) {
			entityManager.render(delta, camera);
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