#include "build.hpp"

void Build::handleEvent(sf::RenderWindow& window, sf::Event& event) {
	if (build_sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		if (s_mouse == Normal) {
			s_mouse = Hovered;
			build_sprite.setTextureRect(sf::IntRect({ 0,s_mouse * 16 }, { 16,16 }));
		}

		if (sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left && s_mouse == Hovered) {
				s_mouse = Pressed;
				if (handler) {
					handler();
				}
			}
		}
	}
	else {
		s_mouse = Normal;
		build_sprite.setTextureRect(sf::IntRect({ 0,s_mouse * 16 }, { 16,16 }));
	}
}