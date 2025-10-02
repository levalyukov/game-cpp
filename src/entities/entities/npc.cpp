#include "npc.hpp"

void NPC::handleEvent(sf::RenderWindow& window, sf::Event& event) {
	if (sprite->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		bool isHovered = sprite->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		switch (event.type) {
			case sf::Event::MouseMoved:
				if (!isPressed) mouseState = isHovered ? Hovered : Normal;
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left && isHovered) {
					mouseState = Pressed;
					isPressed = true;
				}; break;

			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left && isPressed) {
					if (isHovered && mouseState == Pressed) { if (handler) handler(); };
					mouseState = isHovered ? Hovered : Normal;
					isPressed = false;
				}; break;
		};
	};
};

void NPC::render(sf::RenderWindow& window, const float delta, sf::View& game_camera, sf::Clock& clock) {
	window.draw(*sprite);
	window.draw(shadow);
	shadow.setPosition(sprite->getPosition());
};