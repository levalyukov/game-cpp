#include "button.hpp"

void Button::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    bool isHovered = checkHover(window);
    switch (event.type) {
        case sf::Event::MouseMoved:
            if (!isPressed) state = isHovered ? Hovered : Normal;
            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left && isHovered) {
                state = Pressed;
                isPressed = true;
            }
            break;

        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left && isPressed) {
                if (isHovered && state == Pressed) action();
                state = isHovered ? Hovered : Normal;
                isPressed = false;
            }
            break;
    }
}