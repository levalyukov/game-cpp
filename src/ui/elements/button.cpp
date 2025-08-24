#include "button.hpp"

void Button::handleEvent(sf::Event& event, sf::RenderWindow& window) {
	if (getVisible()) {
        bool isHovered = checkHover(window);
        switch (event.type) {
            case sf::Event::MouseMoved:
                if (!isPressed) state = isHovered ? Hovered : Normal;
                if (state == Hovered) {
                    sprite->setTextureRect(sf::IntRect({ 0,sprite_size.y * Hovered }, sprite_size));
                } else if (state == Normal) {
                    sprite->setTextureRect(sf::IntRect({ 0,sprite_size.y * Normal }, sprite_size));
                }
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left && isHovered) {
                    state = Pressed;
                    isPressed = true;
                    sprite->setTextureRect(sf::IntRect({ 0,sprite_size.y * Pressed }, sprite_size));
                }
                break;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left && isPressed) {
                    if (isHovered && state == Pressed) { if (handler) handler(); };
                    state = isHovered ? Hovered : Normal;
                    isPressed = false;
                    sprite->setTextureRect(sf::IntRect({ 0,sprite_size.y * Normal }, sprite_size));
                }
                break;
        }
	}
}

void Button::setText(sf::Font* font, std::string text, unsigned __int8 font_size) {
    label_font = *font;
    label_message = text;
    label_size = font_size;
    label_text.setFont(label_font);
    label_text.setString(label_message);
    label_text.setCharacterSize(label_size);
    label_text.setColor(sf::Color::White);
    label_text.setPosition(
        {
            sprite->getPosition().x + (sprite->getGlobalBounds().width - label_text.getGlobalBounds().width) / 2,
            sprite->getPosition().y + (sprite->getGlobalBounds().height - label_text.getGlobalBounds().height) / 4
        }
    );
}