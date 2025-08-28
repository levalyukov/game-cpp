#pragma once

#include "ui-element.hpp"

#include <functional>
#include <iostream>

class Button : public UIElement {
	public:
		inline Button(
			sf::Texture* button_texture,
			sf::Vector2i size,
			sf::Vector2f coords_pos
		) : texture(std::move(*button_texture)),
			position(coords_pos),
			sprite_size(size) {
			sprite = std::make_unique<sf::Sprite>();
			sprite->setTexture(texture);
			sprite->setTextureRect(sf::IntRect({ 0,0 }, sprite_size));
			sprite->setPosition(position);
			sprite->scale(4, 4);
		};

		std::function<void()> handler = []() {};

		inline sf::Sprite& getSprite() { return *sprite; };

		void setSortIndex(unsigned __int8 new_z_index) override { ZIndex = new_z_index; };
		unsigned __int8 getSortIndex() const override { return ZIndex; };
		inline bool checkHover(sf::RenderWindow& window) { return sprite->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))); }
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handle) override { if (new_handle) handler = new_handle; };
		void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
		inline void render(sf::RenderWindow& window) const override { window.draw(*sprite); };

	private:
		enum State {Normal, Hovered, Pressed};

		std::unique_ptr<sf::Sprite> sprite;
		sf::Vector2i sprite_size;
		sf::Texture& texture;
		sf::Vector2f position;
		State state = Normal;
		bool isPressed = false;
		bool isVisible = true;
		unsigned __int8 ZIndex = 0;

		inline void setState(State new_state) { state = new_state; };
};