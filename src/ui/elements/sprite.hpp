#pragma once

#include "ui-element.hpp"

#include <iostream>
#include <functional>

class Sprite : public UIElement {
	public:
		inline Sprite(
			sf::Texture* sprite_texture,
			sf::Vector2f position_coords
		) : texture(std::move(*sprite_texture)), position(position_coords) {
			sprite = std::make_unique<sf::Sprite>();
			sprite->setTexture(texture);
			sprite->setScale({ 4,4 });
			sprite->setPosition(position);
		};

		std::function<void()> handler = []() {};

		inline sf::Sprite& getSprite() const { return *sprite; }
		inline void setVisible(bool state) override { isVisible = state; };
		inline void setSortIndex(uint8_t new_z_index) override { depth = new_z_index; };
		inline uint8_t getSortIndex() const override { return depth; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> handle) override { if (handle) handler = handle; };
		inline void handleEvent(sf::Event& event, sf::RenderWindow& window, const float delta) override { if (handler) handler(); };
		inline void render(sf::RenderWindow& window) const override { if (sprite) window.draw(*sprite); };

	private:
		std::unique_ptr<sf::Sprite> sprite = nullptr;
		sf::Texture& texture;
		sf::Vector2f position;
		bool isVisible = true;
		uint8_t depth = 0;
};