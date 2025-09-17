#pragma once

#include "elements/label.hpp"
#include "elements/button.hpp"
#include "elements/panel.hpp"
#include "elements/color-rect.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>

class GUI {
	public:
		inline std::unique_ptr<Label> createLabel(
			std::string label_text,
			sf::Font* label_font,
			unsigned __int8 label_size,
			sf::Color label_color,
			sf::Vector2f label_position = { 0.f,0.f }
		) {
			return std::make_unique<Label>(label_text, label_font, label_size, label_color, label_position);
		};

		inline std::unique_ptr<Button> createButton(
			sf::Texture* button_texture,
			sf::Vector2i button_size,
			sf::Vector2f button_position = { 0.f,0.f }
		) {
			return std::make_unique<Button>(button_texture, button_size, button_position);
		};

		inline std::unique_ptr<Panel> createPanel(
			sf::Texture* panel_texture,
			sf::Vector2f panel_position = { 0.f,0.f }
		) {
			return std::make_unique<Panel>(panel_texture, panel_position);
		}

		inline std::unique_ptr<ColorRect> createColorRect(
			sf::Color rect_color,
			sf::Vector2f rect_position = { 0.f,0.f }
		) {
			return std::make_unique<ColorRect>(rect_color, rect_position);
		}
};