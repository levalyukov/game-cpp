#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <iostream>

class ResourceManager {
	public:
		inline static ResourceManager& Instance() {
			static ResourceManager r;
			return r;
		};

		// Textures
		inline void loadTexture(const std::string& name, const std::string& path) {
			auto texture = std::make_unique<sf::Texture>();
			if (!texture->loadFromFile(path)) return;
			textures.emplace(name, std::move(texture));
		};
		inline sf::Texture* getTexture(const std::string name) {
			auto element = textures.find(name);
			return (element != textures.end()) ? element->second.get() : nullptr;
		};
		inline void removeTexture(const std::string name) {
			auto element = textures.find(name);
			if (element != textures.end()) textures.erase(name);
		};

		// Fonts
		inline void loadFont(std::string font_name, std::string path) {
			auto new_font = std::make_unique<sf::Font>();
			if (!new_font->loadFromFile(path)) return;
			fonts.emplace(std::move(font_name), std::move(new_font));
		};
		inline sf::Font* getFont(std::string font_name) {
			auto current_font = fonts.find(font_name);
			return (current_font != fonts.end()) ? current_font->second.get() : nullptr;
		};
		inline void removeFont(std::string font_name) {
			if (fonts.find(font_name) != fonts.end()) fonts.erase(font_name);
		}

	private:
		ResourceManager() {};
		~ResourceManager() {};
		ResourceManager(ResourceManager const&) = delete;
		ResourceManager& operator=(ResourceManager const&) = delete;

		std::map<std::string, std::unique_ptr<sf::Texture>> textures;
		std::map<std::string, std::unique_ptr<sf::Font>> fonts;
};