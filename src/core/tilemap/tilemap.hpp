#pragma once

#include "../globals.hpp"
#include <SFML/Graphics.hpp>

class Tilemap {
	public:
		Tilemap();
		void render(sf::RenderWindow& window);

	private:
		const size_t TILE_SIZE = 64;
		const sf::Vector2i MAP_SIZE = {26,18};
		
		sf::Texture rockTexture;
		sf::Texture waterTexture;
		sf::Texture grassTexture;
		sf::Sprite rockSprite;
		sf::Sprite waterSprite;
		sf::Sprite grassSprite;

		void initilize();
};

