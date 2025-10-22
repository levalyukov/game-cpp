#include "tilemap.hpp"

Tilemap::Tilemap() {
	initilize();
}

void Tilemap::initilize() {
	if (!rockTexture.loadFromFile("../../../assets/textures/location/tiles/rock.png")) return;
	if (!waterTexture.loadFromFile("../../../assets/textures/location/tiles/water.png")) return;
	if (!grassTexture.loadFromFile("../../../assets/textures/location/tiles/grass.png")) return;

	rockSprite.setTexture(rockTexture);
	waterSprite.setTexture(waterTexture);
	grassSprite.setTexture(grassTexture);

	rockSprite.setScale(4, 4);
	waterSprite.setScale(4, 4);
	grassSprite.setScale(4, 4);

	rockSprite.setTextureRect(sf::IntRect({ 0,0 }, { 16,16 }));
	waterSprite.setTextureRect(sf::IntRect({ 0,0 }, { 16,16 }));
	grassSprite.setTextureRect(sf::IntRect({ 0,0 }, { 16,16 }));
}

void Tilemap::render(sf::RenderWindow& window) {
	for (int x = 0; x < MAP_SIZE.x; x++) {
		for (int y = 0; y < MAP_SIZE.y; y++) {

			sf::Vector2f position = { static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE) };

			if (y % 8 == 0) rockSprite.setPosition(position);
			else if (y % 8 == 1) rockSprite.setPosition(position);
			else if (x % 8 == 0) rockSprite.setPosition(position);
			else if (x % 8 == 1) rockSprite.setPosition(position);

			else grassSprite.setPosition(position);

			window.draw(rockSprite);
			//window.draw(waterSprite);
			window.draw(grassSprite);
		}
	}
}