#pragma once

#include "../../core/globals.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <functional>

class UIElement {
	public:
		enum ElementPosition {
			TopLeft, TopCenter, TopRight,
			MiddleLeft, MiddleCenter, MiddleRight,
			BottomLeft, BottomCenter, BottomRight
		};

		void setGlobalPosition(enum ElementPosition current_position, sf::Sprite& sprite);
		void setRelativePosition(enum ElementPosition current_position, sf::Sprite& parent_sprite, sf::Sprite& child_sprite);
		void setMargins(sf::Vector2i vector, sf::Sprite& sprite);

		virtual void setSortIndex(unsigned __int8 new_z_index) = 0;
		virtual unsigned __int8 getSortIndex() const = 0;
		virtual void setVisible(bool state) = 0;
		virtual bool getVisible() const = 0;
		virtual void setHandleEvent(std::function<void()> handle) = 0;
		virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;
		virtual void render(sf::RenderWindow& window) const = 0;
};