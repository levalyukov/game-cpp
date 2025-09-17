#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Entity {
	public:
		virtual float getDepth() const = 0;
		virtual void setHandleEvent(std::function<void()> new_handler) = 0;
		virtual void handleEvent(sf::RenderWindow& window, sf::Event& event) = 0;
		virtual void render(sf::RenderWindow& window, float delta_time, sf::View& game_camera, sf::Clock& clock) = 0;
};