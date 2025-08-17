#include "build.hpp"

void Build::handleEvent(sf::RenderWindow& window, sf::Event& event) {
	if (build_sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		if (handler) {
			handler();
			//build_sprite.setTextureRect(sf::IntRect({},{}));
		}
	}
}