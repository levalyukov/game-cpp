#pragma once

#include "../../core/globals.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

class UIElement {
	public:
		enum ElementPosition {
			TopLeft, TopCenter, TopRight,
			MiddleLeft, MiddleCenter, MiddleRight,
			BottomLeft, BottomCenter, BottomRight
		};

		void setGlobalPosition(enum ElementPosition position, sf::Sprite& sprite);
		void setRelativePosition(enum ElementPosition position, sf::Sprite& parent, sf::Sprite& child, sf::Vector2f margins = { 0.f,0.f });
		void setRelativePositionText(enum ElementPosition position, sf::Sprite& parent, sf::Text& child, sf::Vector2f margins = { 0.f,0.f });

		virtual void setSortIndex(unsigned __int8 new_z_index) = 0;
		virtual unsigned __int8 getSortIndex() const = 0;
		virtual void setVisible(bool state) = 0;
		virtual bool getVisible() const = 0;
		virtual void setHandleEvent(std::function<void()> handle) = 0;
		virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;
		virtual void render(sf::RenderWindow& window) const = 0;
};