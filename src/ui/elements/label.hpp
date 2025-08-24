#pragma once

#include "ui-element.hpp"

class Label : public UIElement {
	public:
		inline Label(
			std::string message,
			sf::Font* font,
			unsigned __int8 size,
			sf::Color color,
			sf::Vector2f coords_position
		) : message(message),
			font(*font),
			size(size),
			color(color) {
			text.setFont(*font);
			text.setCharacterSize(size);
			text.setColor(color);
			text.setString(message);
			text.setPosition(coords_position);
		};

		std::function<void()> handler;

		inline void setText(std::string new_msg) { message = new_msg; text.setString(new_msg); };
		inline void setColor(sf::Color new_color) { color = new_color; text.setColor(color); };
		inline void setSize(unsigned __int8 new_size) { size = new_size; text.setCharacterSize(size); };

		void setSortIndex(unsigned __int8 new_z_index) override { ZIndex = new_z_index; };
		unsigned __int8 getSortIndex() const override { return ZIndex; };
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handler) {};
		inline void handleEvent(sf::Event& event, sf::RenderWindow& window) override {};
		inline void render(sf::RenderWindow& window) const override { window.draw(text); };

	private:
		std::string message;
		const sf::Font& font;
		unsigned __int8 size;
		sf::Text text;
		sf::Color color;
		bool isVisible = true;
		unsigned __int8 ZIndex = 0;
};