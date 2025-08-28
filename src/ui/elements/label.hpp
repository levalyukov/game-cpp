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
		) : font(*font) {
			text->setFont(*font);
			text->setCharacterSize(size);
			text->setColor(color);
			text->setString(message);
			text->setPosition(coords_position);
		};

		std::function<void()> handler;

		inline sf::Text& getText() const { return *text; };
		inline void setMessage(std::string new_msg) { text->setString(new_msg); };
		inline void setColor(sf::Color new_color) { text->setColor(new_color); };
		inline void setSize(unsigned __int8 new_size) { text->setCharacterSize(new_size); };
		inline void setPosition(sf::Vector2f new_position) { text->setPosition(new_position); };

		void setSortIndex(unsigned __int8 new_z_index) override { sortIndex = new_z_index; };
		unsigned __int8 getSortIndex() const override { return sortIndex; };
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handler) {};
		inline void handleEvent(sf::Event& event, sf::RenderWindow& window) override {};
		inline void render(sf::RenderWindow& window) const override { window.draw(*text); };

	private:
		std::unique_ptr<sf::Text> text = std::make_unique<sf::Text>();
		const sf::Font& font;
		bool isVisible = true;
		unsigned __int8 sortIndex = 0;
};