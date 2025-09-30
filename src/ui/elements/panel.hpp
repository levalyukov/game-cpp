#pragma once

#include "ui-element.hpp"

#include <iostream>
#include <functional>

class Panel : public UIElement {
	public:
		inline Panel(
			sf::Texture* panel_texture,
			sf::Vector2f position_coords
		) : texture(std::move(*panel_texture)), position(position_coords) {
			panel->setTexture(texture);
			panel->setScale({ 4,4 });
			panel->setPosition(position);
		};

		std::function<void()> handler = []() {};

		inline sf::Vector2f getElementPosition() const override { return panel->getPosition(); }
		inline void setSortIndex(__int8 new_z_index) override { depth = new_z_index; };
		inline __int8 getSortIndex() const override { return depth; };
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline sf::Sprite& getSprite() const { return *panel; }
		inline void setHandleEvent(std::function<void()> handle) override { if (handle) handler = handle; };
		inline void handleEvent(sf::Event& event, sf::RenderWindow& window) override { if (handler) handler(); };
		inline void render(sf::RenderWindow& window) const override { window.draw(*panel); };

	private:
		std::unique_ptr<sf::Sprite> panel = std::make_unique<sf::Sprite>();
		sf::Texture& texture;
		sf::Vector2f position;
		bool isVisible = true;
		__int8 depth = 0;
};