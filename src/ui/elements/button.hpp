#pragma once

#include "ui-element.hpp"

#include <functional>
#include <iostream>

class Button : public UIElement {
	public:
		Button(
			sf::Texture* default_texture,
			sf::Vector2i button_size,
			sf::Vector2f posisiton
		) : defaultTexture(*default_texture),
			size(button_size) {
			sprite = std::make_unique<sf::Sprite>();
			icon = std::make_unique<sf::Sprite>();
			iconTexture = std::make_unique<sf::Texture>();
			sprite->setTexture(defaultTexture);
			sprite->setTextureRect(sf::IntRect({ 0,0 }, size));
			sprite->setPosition(posisiton);
			sprite->scale(4, 4);
		};

		std::function<void()> handler = []() {};

		inline void setIcon(std::string texture_path) {
			if (!iconTexture->loadFromFile(texture_path)) return;
			icon->setTexture(*iconTexture);
			icon->setPosition(sprite->getPosition());
			icon->setTextureRect(sf::IntRect({ 0,0 }, { 12 * 4,12 * 4 }));
		};
		inline sf::Sprite& getIcon() const { return *icon; };
		inline sf::Sprite& getSprite() const { return *sprite; };
		inline void setSortIndex(uint8_t new_index) override { depth = new_index; };
		inline uint8_t getSortIndex() const override { return depth; };
		inline bool checkHover(sf::RenderWindow& window) { return sprite->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))); };
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handle) override { if (new_handle) handler = new_handle; };
		inline void render(sf::RenderWindow& window) const override { if (sprite) window.draw(*sprite); if (icon) window.draw(*icon); };
		void handleEvent(sf::Event& event, sf::RenderWindow& window, const float delta) override;

		~Button() { sprite = nullptr; icon = nullptr; iconTexture = nullptr; };

	private:
		enum State {Disabled, Normal, Hovered, Pressed};
		State state = Normal;

		std::unique_ptr<sf::Sprite> icon;
		std::unique_ptr<sf::Texture> iconTexture;

		std::unique_ptr<sf::Sprite> sprite;
		sf::Texture& defaultTexture;
		sf::Vector2i size;

		bool isPressed = false;
		bool isVisible = true;
		bool isDisabled = false;

		uint8_t depth = 0;
};