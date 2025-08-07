#pragma once

#include "ui-element.hpp"

#include <functional>
#include <iostream>

class Button : public UIElement {
	public:
		Button(
			sf::Texture* button_texture,
			sf::Vector2f coords_pos
		) : texture(std::move(*button_texture)),
			position(coords_pos) {
			sprite = std::make_unique<sf::Sprite>();
			sprite->setTexture(texture);
			sprite->setTextureRect(sf::IntRect({ 0,0 }, { 48,16 }));
			sprite->setPosition(position);
			sprite->scale(4, 4);
		};

		std::function<void()> handler = []() {};

		void setText(sf::Font* font, std::string text, unsigned __int8 font_size);
		inline void changeText(std::string new_text) { label_message = new_text; };
		inline void setElementPosition(sf::Vector2f new_position) { sprite->setPosition(new_position); };
		inline sf::Sprite& getButtonSprite() { return *sprite; };

		inline bool checkHover(sf::RenderWindow& window) { return sprite->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))); }
		inline void setIndex(unsigned __int8 new_z_index) override { zIndex = new_z_index; };
		inline unsigned __int8 getIndex() const override { return zIndex; };
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handle) override { if (new_handle) handler = new_handle; };
		void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
		inline void render(sf::RenderWindow& window) const override { window.draw(*sprite); window.draw(label_text); };

	private:
		enum State {Normal, Hovered, Pressed};

		std::unique_ptr<sf::Sprite> sprite;
		sf::Texture& texture;
		sf::Vector2f position;
		State state = Normal;
		bool isPressed = false;
		bool isVisible = true;
		unsigned __int8 zIndex = 0;

		sf::Font label_font;
		sf::Text label_text;
		sf::String label_message;
		unsigned __int8 label_size = 24;
		//ElementPosition label_position;

		inline void setState(State new_state) { state = new_state; };
};