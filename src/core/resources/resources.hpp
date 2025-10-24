#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <map>
#include <string>
#include <cctype>
#include <algorithm>

class ResourceManager {
	public:
		// Textures
		inline void loadTexture(const std::string name, const std::string path) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) {return std::tolower(c); });
			std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
			if (!texture->loadFromFile(path)) return;
			textures.emplace(lower_name, std::move(texture));
		};

		inline sf::Texture* getTexture(const std::string name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) {return std::tolower(c); });
			auto element = textures.find(lower_name);
			return (element != textures.end()) ? element->second.get() : nullptr;
		};

		inline void removeTexture(const std::string name) {
			std::string lower_name = name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) {return std::tolower(c); });
			auto element = textures.find(lower_name);
			if (element != textures.end()) textures.erase(lower_name);
		};

		// Fonts
		inline void loadFont(const std::string font_name, std::string path) {
			std::string lower_name = font_name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) {return std::tolower(c); });
			auto new_font = std::make_unique<sf::Font>();
			if (!new_font->loadFromFile(path)) return;
			fonts.emplace(std::move(lower_name), std::move(new_font));
		};

		inline sf::Font* getFont(const std::string font_name) {
			std::string lower_name = font_name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) {return std::tolower(c); });
			auto current_font = fonts.find(lower_name);
			return (current_font != fonts.end()) ? current_font->second.get() : nullptr;
		};

		inline void removeFont(const std::string font_name) {
			std::string lower_name = font_name;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) {return std::tolower(c); });
			if (fonts.find(lower_name) != fonts.end()) fonts.erase(lower_name);
		};

	private:
		std::map<std::string, std::unique_ptr<sf::Texture>> textures;
		std::map<std::string, std::unique_ptr<sf::Font>> fonts;
};