#pragma once

#include "globals.hpp"
#include "resources/resources.hpp"
#include "tilemap/tilemap.hpp"
#include "../world/world.hpp"
#include "../ui/ui-manager.hpp"
#include "../ui/screens/ui.hpp"
#include "../mechanics/cooking-manager.hpp"
#include "../mechanics/inventory-manager.hpp"
#include "../mechanics/economy-manager.hpp"
#include "../mechanics/glocery-shop-manager.hpp"

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
			resourceManager = nullptr;
			entityManager = nullptr;
			cookingManager = nullptr;
			uiManager = nullptr;
			ui = nullptr;
			world = nullptr;
			tilemap = nullptr;
		};

	private:
		std::unique_ptr<ResourceManager> resourceManager = std::make_unique<ResourceManager>();
		std::unique_ptr<EntityManager> entityManager = std::make_unique<EntityManager>();
		std::unique_ptr<CookingManager> cookingManager = std::make_unique<CookingManager>();
		std::unique_ptr<UIManager> uiManager = std::make_unique<UIManager>();
		std::unique_ptr<InventoryManager> inventoryManager = std::make_unique<InventoryManager>();
		std::unique_ptr<EconomyManager> economyManager = std::make_unique<EconomyManager>();
		std::unique_ptr<GloceryShopManager> gloceryShopManager = std::make_unique<GloceryShopManager>();

		std::unique_ptr<UI> ui = std::make_unique<UI>(*uiManager, *resourceManager, *cookingManager, *inventoryManager, *economyManager, *gloceryShopManager);
		std::unique_ptr<World> world = std::make_unique<World>(*uiManager, *entityManager, *resourceManager, *cookingManager, *inventoryManager, *economyManager, *ui->getInventory(), *ui->getHUD());
		std::unique_ptr<Tilemap> tilemap = std::make_unique<Tilemap>();

		Globals& globals = Globals::instance();
		sf::RenderWindow& window = globals.getWindow();
		sf::Event& event = globals.getEvent();
		sf::Clock& clock = globals.getClock();
		sf::View main_camera = window.getDefaultView();
		sf::View ui_camera = window.getDefaultView();
		sf::Image icon;
		const sf::Uint8* iconData = {};

		void processEvent();
		void render();
		void run();

		float delta = std::min(clock.restart().asSeconds(), .1f);
};