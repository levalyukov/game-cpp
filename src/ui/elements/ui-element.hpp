#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <functional>

class UIElement {
	public:
		enum ElementPosition {
			TopLeft, TopCenter, TopRight,
			MiddleLeft, MiddleCenter, MiddleRight,
			BottomLeft, BottomCenter, BottomRight
		};

		virtual void setIndex(unsigned __int8 new_z_index) = 0;
		virtual unsigned __int8 getIndex() const = 0;
		virtual void setVisible(bool state) = 0;
		virtual bool getVisible() const = 0;
		virtual void setHandleEvent(std::function<void()> handle) = 0;
		virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;
		virtual void render(sf::RenderWindow& window) const = 0;
};