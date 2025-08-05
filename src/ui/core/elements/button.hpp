#pragma once

#include "ui-element.hpp"

#include <functional>

class Button : public UIElement {
	public:
		using ButtonAction = std::function<void()>;

		Button(
			sf::Texture* button_texture,
			sf::Vector2f coords_pos
		) : texture(button_texture),
			position(coords_pos) {
			sprite.setTexture(*texture);
			sprite.setTextureRect(sf::IntRect(0, 16, 32, 16));
			sprite.setPosition(position);
			sprite.scale(4, 4);
		};

		using ElementAction = std::function<void()>;

		inline void setAction(ButtonAction function) { action = function; };
		inline bool checkHover(sf::RenderWindow& window) { return sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))); }
		inline void setVisible() { isVisible = !isVisible; };
		inline bool getVisible() override { return isVisible; };
		inline void setHandleEvent(ElementAction new_action) override { action = new_action; };
		void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
		inline void render(sf::RenderWindow& window) const override { window.draw(sprite); };

	private:
		enum State {Normal, Hovered, Pressed};

		sf::Sprite sprite;
		sf::Texture* texture;
		sf::Vector2f position;
		State state;
		bool isPressed;
		ElementAction action;
		bool isVisible = true;

		inline void setState(State new_state) { state = new_state; };
};