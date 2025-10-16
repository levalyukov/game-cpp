#include "button.hpp"

void Button::handleEvent(
    sf::Event& event, 
    sf::RenderWindow& window,
    const float delta
) {
	if (getVisible()) {
        if (isDisabled) {
            sprite->setTextureRect(sf::IntRect({ 0,size.y * Disabled }, size));
            return;
        };

        bool isHovered = checkHover(window);
        switch (event.type) {
            case sf::Event::MouseMoved:
                if (!isPressed) state = isHovered ? Hovered : Normal;
                if (state == Hovered) {
                    sprite->setTextureRect(sf::IntRect({ 0,size.y * Hovered }, size));
                } else if (state == Normal) {
                    sprite->setTextureRect(sf::IntRect({ 0,size.y * Normal }, size));
                };  break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left && isHovered) {
                    state = Pressed;
                    isPressed = true;
                    sprite->setTextureRect(sf::IntRect({ 0,size.y * Pressed }, size));
                }; break;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left && isPressed) {
                    if (isHovered && state == Pressed) { if (handler) handler(); };
                    state = isHovered ? Hovered : Normal;
                    isPressed = false;
                    sprite->setTextureRect(sf::IntRect({ 0,size.y * Normal }, size));
                }; break;
        };
    };
};