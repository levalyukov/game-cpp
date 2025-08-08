#pragma once

#include "globals.hpp"
#include "tilemap/tilemap.hpp"
#include "../world/world.hpp"
#include "../ui/ui-manager.hpp"
#include "../ui/screens/ui.hpp"

class Game {
	public:
		Game() {
			window.setFramerateLimit(60);
			if (!icon.loadFromFile("../../../assets/icon.png")) return;
			iconData = icon.getPixelsPtr();
			window.setIcon(icon.getSize().x, icon.getSize().y, iconData);
		}
		void run();

	protected:
		Globals& globals = Globals::instance();
		UIManager& UIManager = UIManager::instance();
		sf::RenderWindow& window = globals.getWindow();
		sf::Event& event = globals.getEvent();
		sf::Clock& clock = globals.getClock();
		sf::View main_camera = window.getDefaultView();
		sf::View ui_camera = window.getDefaultView();
		sf::Image icon;
		const sf::Uint8* iconData;

		void processEvent();
		void render();

		UI ui;
		Tilemap tilemap;
		World world;

		float delta = std::min(clock.restart().asSeconds(), .1f);
};