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
			panel = std::make_unique<sf::Sprite>();
			panel->setTexture(texture);
			panel->setScale({ 4,4 });
			panel->setPosition(position);
		};

		std::function<void()> handler = []() {};

		inline sf::Vector2f getElementPosition() const { return panel->getPosition(); };
		inline sf::Sprite& getButtonSprite() const { return *panel; };

		void setSortIndex(unsigned __int8 new_z_index) override { ZIndex = new_z_index; };
		unsigned __int8 getSortIndex() const override { return ZIndex; };
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline sf::Sprite& getSprite() const { return *panel; };

		inline void setHandleEvent(std::function<void()> handle) override { if (handle) handler = handle; };
		inline void handleEvent(sf::Event& event, sf::RenderWindow& window) override { if (handler) handler(); };
		inline void render(sf::RenderWindow& window) const override { window.draw(*panel); };

	private:
		std::unique_ptr<sf::Sprite> panel;
		sf::Texture& texture;
		sf::Vector2f position;
		bool isVisible = true;
		unsigned __int8 ZIndex = 0;
};