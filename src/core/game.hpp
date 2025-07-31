#pragma once

#include "tilemap/tilemap.hpp"
#include "resources/resources.hpp"

#include "../entities/entity-manager.hpp"
#include "../ui/core/ui.hpp"
#include "../ui/screens/hud.hpp"
#include "../entities/entities/player.hpp"

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

		ResourceManager& resourceManager = ResourceManager::Instance();
		UIManager& UIManager = UIManager::Instance();
		EntityManager& entityManager = EntityManager::Instance();

		Tilemap tilemap;
		HUD hud;

		sf::Image icon;
		const sf::Uint8* iconData;

		float rawDelta = clock.restart().asSeconds();
		float deltaTime = std::min(rawDelta, 0.1f);
};