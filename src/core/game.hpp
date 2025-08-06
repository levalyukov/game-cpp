#pragma once

#include "tilemap/tilemap.hpp"
#include "resources/resources.hpp"
#include "states.hpp"

#include "../ui/ui-manager.hpp"
#include "../ui/screens/ui.hpp"
#include "../world/world.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System/Err.hpp>

class Game {
	public:
		Game();
		void run();

	private:
		const std::string WINDOW_TITLE = "Delicious Soup";
		unsigned int WINDOW_WIDTH = 1280;
		unsigned int WINDOW_HEGHT = 720;

		sf::RenderWindow window;
		sf::Color background = sf::Color(0,0,0);
		sf::Event event;
		sf::Clock clock;
		sf::View gameCamera;
		sf::View UIView;

		void processEvent();
		void render();
		inline void initilizeIcon() {
			if (!icon.loadFromFile("../../../assets/icon.png")) {
				return;
			};
			iconData = icon.getPixelsPtr();
			window.setIcon(icon.getSize().x, icon.getSize().y, iconData);
		};

		World world;
		Tilemap tilemap;
		GameState& gameState = GameState::instance();

		/*! UI */
		UIManager& UIManager = UIManager::instance();
		UI ui;
		/* --- */

		sf::Image icon;
		const sf::Uint8* iconData;
		float rawDelta = clock.restart().asSeconds();
		float deltaTime = std::min(rawDelta, 0.1f);
};