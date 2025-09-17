#pragma once

#include "ui-element.hpp"

#include <functional>
#include <iostream>

class Button : public UIElement {
	public:
		Button(
			sf::Texture* button_texture,
			sf::Vector2i button_size,
			sf::Vector2f button_pos
		) : texture(*button_texture),
			size(button_size) {
			sprite = std::make_unique<sf::Sprite>();
			icon = std::make_unique<sf::Sprite>();
			icon_txtr = std::make_unique<sf::Texture>();
			sprite->setTexture(texture);
			sprite->setTextureRect(sf::IntRect({ 0,0 }, size));
			sprite->setPosition(button_pos);
			sprite->scale(4, 4);
		};

		~Button() {
			sprite = nullptr;
			icon = nullptr;
			icon_txtr = nullptr;
		}

		std::function<void()> handler = []() {};

		inline void setIcon(std::string texture_path) {
			if (!icon_txtr->loadFromFile(texture_path)) return;
			icon->setTexture(*icon_txtr);
			icon->setPosition(sprite->getPosition());
			icon->setTextureRect(sf::IntRect({ 0,0 }, { 12*4,12*4 }));
		}
		inline sf::Sprite& getIcon() const { return *icon; };
		inline sf::Sprite& getSprite() const { return *sprite; };
		inline sf::Vector2f getElementPosition() const override { return sprite->getPosition(); };
		inline void setSortIndex(unsigned __int8 new_index) override { depth = new_index; };
		inline unsigned __int8 getSortIndex() const override { return depth; };
		inline bool checkHover(sf::RenderWindow& window) { return sprite->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))); }
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handle) override { if (new_handle) handler = new_handle; };
		inline void render(sf::RenderWindow& window) const override { window.draw(*sprite); if (icon) window.draw(*icon); };
		void handleEvent(sf::Event& event, sf::RenderWindow& window) override;

	private:
		enum State {Normal, Hovered, Pressed};
		State state = Normal;

		//// icon ////
		std::unique_ptr<sf::Sprite> icon;
		std::unique_ptr<sf::Texture> icon_txtr;
		//////////////

		std::unique_ptr<sf::Sprite> sprite;
		sf::Texture& texture;
		sf::Vector2i size;
		bool isPressed = false;
		bool isVisible = true;
		unsigned __int8 depth = 0;

		inline void setState(State new_state) { state = new_state; };
};