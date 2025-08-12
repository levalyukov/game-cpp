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
			std::string message,
			sf::Font* font,
			unsigned __int8 size,
			sf::Color color,
			UIElement::ElementPosition position,
			sf::Vector2f coords_pos = { 0,0 }
		) {
			return std::make_unique<Label>(message, font, size, color, coords_pos, position);
		};

		inline std::unique_ptr<Button> createButton(
			sf::Texture* texture,
			sf::Vector2f coords_pos = { 0,0 }
		) {
			return std::make_unique<Button>(texture, coords_pos);
		};

		inline std::unique_ptr<Panel> createPanel(
			sf::Texture* panel_texture,
			sf::Vector2f position_coords = { 0,0 }
		) {
			return std::make_unique<Panel>(panel_texture, position_coords);
		}

		inline std::unique_ptr<ColorRect> createColorRect(
			sf::Color color,
			sf::Vector2f size = { 0.f,0.f }
		) {
			return std::make_unique<ColorRect>(color, size);
		}
};