#pragma once

#include "globals.hpp"
#include "resources/resources.hpp"
#include "tilemap/tilemap.hpp"

#include "../world/world.hpp"
#include "../ui/ui-manager.hpp"
#include "../ui/screens/ui.hpp"

#include "../mechanics/cooking-manager.hpp"
#include "../mechanics/economy-manager.hpp"
#include "../mechanics/rating-manager.hpp"
#include "../mechanics/glocery-shop-manager.hpp"
#include "../mechanics/event-manager.hpp"
#include "../mechanics/items.hpp"

#include <memory>

class Game {
	public:
		Game() {
			window.setFramerateLimit(60);
			if (!icon.loadFromFile("../../../assets/icon.png")) return;
			iconData = icon.getPixelsPtr();
			window.setIcon(icon.getSize().x, icon.getSize().y, iconData);
			run();
		};

		~Game() {
			resourceManager = nullptr; entityManager = nullptr;
			cookingManager = nullptr; uiManager = nullptr;
			ui = nullptr; world = nullptr; tilemap = nullptr;
		};

	private:
		Globals& globals = Globals::instance();
		sf::RenderWindow& window = globals.getWindow();
		sf::Event& event = globals.getEvent();
		sf::Clock& clock = globals.getClock();
		sf::View main_camera = window.getDefaultView();
		sf::View ui_camera = window.getDefaultView();
		sf::Image icon;
		const sf::Uint8* iconData = {};

		std::unique_ptr<Items> itemsContainer = std::make_unique<Items>();
		std::unique_ptr<EventManager> eventManager = std::make_unique<EventManager>();
		std::unique_ptr<ResourceManager> resourceManager = std::make_unique<ResourceManager>();
		std::unique_ptr<EntityManager> entityManager = std::make_unique<EntityManager>();
		std::unique_ptr<CookingManager> cookingManager = std::make_unique<CookingManager>(*itemsContainer);
		std::unique_ptr<UIManager> uiManager = std::make_unique<UIManager>();
		std::unique_ptr<EconomyManager> economyManager = std::make_unique<EconomyManager>();
		std::unique_ptr<GloceryShopManager> gloceryShopManager = std::make_unique<GloceryShopManager>();
		std::unique_ptr<WarehouseManager> warehouseManager = std::make_unique<WarehouseManager>();
		std::unique_ptr<OrdersManager> ordersManager = std::make_unique<OrdersManager>();
		std::unique_ptr<Rating> ratingManager = std::make_unique<Rating>();

		std::unique_ptr<UI> ui = std::make_unique<UI>(
			*uiManager, *resourceManager, *cookingManager, 
			*economyManager, *gloceryShopManager, *warehouseManager, 
			*ordersManager);
		std::unique_ptr<World> world = std::make_unique<World>(
			*uiManager, *entityManager, *resourceManager, 
			*cookingManager, *economyManager, *eventManager, 
			*ordersManager, *itemsContainer, *ui);
		std::unique_ptr<Tilemap> tilemap = std::make_unique<Tilemap>();

		void processEvent();
		void render();
		void run();

		float delta = clock.restart().asSeconds();
};