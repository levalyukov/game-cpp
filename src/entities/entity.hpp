#pragma once

#include <SFML/Graphics.hpp>

class Entity {
	public:
		virtual float getDepth() const = 0;
		virtual void handleEvent(sf::RenderWindow& window, sf::Event& event) = 0;
		virtual void render(sf::RenderWindow& window, float deltaTime, sf::View& gameCamera, sf::Clock& clock) = 0;
};