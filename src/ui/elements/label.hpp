#pragma once

#include <string>
#include <stdint.h>
#include "ui-element.hpp"

class Label : public UIElement {
	public:
		inline Label(
			std::wstring message,
			sf::Font* font,
			uint8_t size,
			sf::Color color,
			sf::Vector2f coords_position
		) : font(std::move(*font)) {
			text = std::make_unique<sf::Text>();
			text->setFont(*font);
			text->setCharacterSize(size);
			text->setColor(color);
			text->setString(message);
			text->setPosition(coords_position);
		};

		inline sf::Text& getText() const { return *text; };
		inline void setMessage(std::wstring message) { text->setString(message); };
		inline void setColor(sf::Color color) { text->setColor(color); };
		inline void setSize(uint8_t size) { text->setCharacterSize(size); };
		inline void setPosition(sf::Vector2f position) { text->setPosition(position); };
		inline void setSortIndex(uint8_t z_index) override { depth = z_index; };
		inline uint8_t getSortIndex() const override { return depth; };
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handler) {};
		inline void handleEvent(sf::Event& event, sf::RenderWindow& window, const float delta) override {};
		inline void render(sf::RenderWindow& window) const override { if (text) window.draw(*text); };

	private:
		std::unique_ptr<sf::Text> text = nullptr;
		const sf::Font&& font;
		bool isVisible = true;
		uint8_t depth = 0;
};