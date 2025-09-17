#include "build.hpp"

void Build::handleEvent(sf::RenderWindow& window, sf::Event& event) {
	bool isHovered = sprite->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	switch (event.type) {
		case sf::Event::MouseMoved:
			if (!isPressed) m_state = isHovered ? Hovered : Normal;
			if (m_state == Hovered) {
				sprite->setTextureRect(sf::IntRect({ 0,build_size.y * Hovered }, build_size));
			}
			else if (m_state == Normal) {
				sprite->setTextureRect(sf::IntRect({ 0,build_size.y * Normal }, build_size));
			}
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left && isHovered) {
				m_state = Pressed;
				isPressed = true;
				sprite->setTextureRect(sf::IntRect({ 0,build_size.y * Pressed }, build_size));
			}
			break;

		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left && isPressed) {
				if (isHovered && m_state == Pressed) { if (handler) handler(); };
				m_state = isHovered ? Hovered : Normal;
				isPressed = false;
				sprite->setTextureRect(sf::IntRect({ 0,build_size.y * Normal }, build_size));
			}
			break;
	}
}