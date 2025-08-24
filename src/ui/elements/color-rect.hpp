#pragma once

#include "ui-element.hpp"
#include <functional>

class ColorRect : public UIElement {
	public:
		inline ColorRect(
			sf::Color color,
			sf::Vector2f size
		) : color_rect(color),
			size_rect(size) {
			rect.setFillColor(color_rect);
			rect.setSize(size_rect);
		};

		std::function<void()> handler;

		void setSortIndex(unsigned __int8 new_z_index) override { ZIndex = new_z_index; };
		unsigned __int8 getSortIndex() const override { return ZIndex; };

		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handle) override { handler = new_handle; };
		inline void handleEvent(sf::Event& event, sf::RenderWindow& window) override { if (handler) handler(); };
		inline void render(sf::RenderWindow& window) const override { window.draw(rect); };

	protected:
		sf::RectangleShape rect;
		sf::Color color_rect;
		sf::Vector2f size_rect;
		bool isVisible = true;
		unsigned __int8 ZIndex = 0;
};