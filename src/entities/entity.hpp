#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

class Entity {
	public:
		virtual float getDepth() const = 0;
		virtual void setHandler(std::function<void()> new_handler) = 0;
		virtual void setEvent(std::function<void()> new_event) = 0;
		virtual void handler(sf::RenderWindow& window, sf::Event& event) = 0;
		virtual void event(sf::RenderWindow& window, sf::Event& event) = 0;
		virtual void render(sf::RenderWindow& window, const float delta, sf::View& game_camera, sf::Clock& clock) = 0;
};