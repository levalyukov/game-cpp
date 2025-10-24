#pragma once

#include "ui-element.hpp"
#include <functional>

class ColorRect : public UIElement {
	public:
		inline ColorRect(
			sf::Color _color,
			sf::Vector2f size
		) : color(_color) {
			rect.setFillColor(color);
			rect.setSize(size);
		};

		std::function<void()> handler;

		//inline sf::RectangleShape& getRect() const { return *rect; };
		inline void setNewRectSize(sf::Vector2f new_size) { rect.setSize(new_size); };
		inline void setSortIndex(uint8_t new_z_index) override { depth = new_z_index; };
		inline uint8_t getSortIndex() const override { return depth; };
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handle) override { handler = new_handle; };
		inline void handleEvent(sf::Event& event, sf::RenderWindow& window, const float delta) override { if (handler) handler(); };
		inline void render(sf::RenderWindow& window) const override { window.draw(rect); };

	protected:
		sf::RectangleShape rect;
		sf::Color color;
		bool isVisible = true;
		uint8_t depth = 0;
};