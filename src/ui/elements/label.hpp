#pragma once

#include "ui-element.hpp"

class Label : public UIElement {
	public:
		Label(
			std::string message,
			sf::Font* font,
			unsigned __int8 size,
			sf::Color color,
			sf::Vector2f coords_position,
			ElementPosition position
		) : message(message),
			font(*font),
			size(size),
			color(color),
			coords_pos(coords_position),
			position(position) {
			text.setFont(*font);
			text.setCharacterSize(size);
			text.setColor(color);
			text.setString(message);
			text.setPosition(coords_position);
		};

		using ElementAction = std::function<void()>;

		inline void setText(std::string new_msg) { message = new_msg; text.setString(new_msg); };
		inline void setColor(sf::Color new_color) { color = new_color; text.setColor(color); };
		inline void setSize(unsigned __int8 new_size) { size = new_size; text.setCharacterSize(size); };

		inline void setIndex(unsigned __int8 new_z_index) override { zIndex = new_z_index; };
		inline unsigned __int8 getIndex() const override { return zIndex; };
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(ElementAction new_func) { action = new_func; };
		inline void handleEvent(sf::Event& event, sf::RenderWindow& window) override {};
		inline void render(sf::RenderWindow& window) const override { window.draw(text); };

	private:
		std::string message;
		const sf::Font& font;
		unsigned __int8 size;
		sf::Text text;
		sf::Color color;
		sf::Vector2f coords_pos;
		ElementPosition position;
		ElementAction action;
		bool isVisible = true;
		unsigned __int8 zIndex;
};