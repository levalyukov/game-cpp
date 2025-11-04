#pragma once

#include "elements/label.hpp"
#include "elements/button.hpp"
#include "elements/sprite.hpp"
#include "elements/color-rect.hpp"
#include "elements/progress-bar.hpp"

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>

class GUI {
	public:
		inline std::unique_ptr<Label> createLabel(
			std::wstring label_text,
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

		inline std::unique_ptr<Sprite> createSprite(
			sf::Texture* sprite_texture,
			sf::Vector2f sprite_position = { 0.f,0.f }
		) {
			return std::make_unique<Sprite>(sprite_texture, sprite_position);
		};

		inline std::unique_ptr<ColorRect> createColorRect(
			sf::Color rect_color,
			sf::Vector2f rect_position = { 0.f,0.f }
		) {
			return std::make_unique<ColorRect>(rect_color, rect_position);
		};

		inline std::unique_ptr<ProgressBar> createProgressBar(
			sf::Texture* bar_texture,
			sf::Vector2i bar_size
		) {
			return std::make_unique<ProgressBar>(bar_texture, bar_size);
		};
};