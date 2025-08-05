#pragma once

#include "ui-element.hpp"

#include <iostream>
#include <functional>

class Panel : public UIElement {
	public:
		Panel(
			sf::Texture* panel_texture,
			sf::Vector2f position_coords
		) : texture(std::move(*panel_texture)), position(position_coords) {
			panel.setTexture(texture);
			panel.setScale({ 4,4 });
			panel.setPosition(position);
		};

		std::function<void()> handler = []() {};

		inline void setVisible() { isVisible = !isVisible; };
		inline bool getVisible() override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handler) override { 
			if (new_handler) { 
				handler = new_handler; 
			} 
		};
		inline void handleEvent(sf::Event& event, sf::RenderWindow& window) override {
			if (handler) {
				handler();
			}
		};
		inline void render(sf::RenderWindow& window) const override { window.draw(panel); };

	private:
		sf::Sprite panel;
		sf::Texture& texture;
		sf::Vector2f position;
		bool isVisible = true;
};