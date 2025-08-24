#include "ui-element.hpp"

void UIElement::setGlobalPosition(
	enum ElementPosition current_position, 
	sf::Sprite& sprite
) {
	sf::RenderWindow& window = Globals::instance().getWindow();
	float windowSizeX = static_cast<float>(window.getSize().x);
	float windowSizeY = static_cast<float>(window.getSize().y);
	float spriteSizeWidth = static_cast<float>(sprite.getGlobalBounds().width);
	float spriteSizeHeight = static_cast<float>(sprite.getGlobalBounds().height);

	switch (current_position) {
		case TopLeft:
			sprite.setPosition({ 0,0 });
			break;
		case TopCenter:
			sprite.setPosition({ (windowSizeX - spriteSizeWidth) / 2.f, 0 });
			break;
		case TopRight:
			sprite.setPosition({ windowSizeX - spriteSizeWidth, 0 });
			break;

		case MiddleLeft:
			sprite.setPosition({ 0, (windowSizeY - spriteSizeHeight) / 2.f });
			break;
		case MiddleCenter:
			sprite.setPosition({ (windowSizeX - spriteSizeWidth) / 2.f, (windowSizeY - spriteSizeHeight) / 2.f });
			break;
		case MiddleRight:
			sprite.setPosition({ windowSizeX - spriteSizeWidth, (windowSizeY - spriteSizeHeight) / 2.f });
			break;

		case BottomLeft:
			sprite.setPosition({ 0, windowSizeY - spriteSizeHeight });
			break;
		case BottomCenter:
			sprite.setPosition({ (windowSizeX - spriteSizeWidth) / 2.f, windowSizeY - spriteSizeHeight });
			break;
		case BottomRight:
			sprite.setPosition({ windowSizeX - spriteSizeWidth, windowSizeY - spriteSizeHeight });
			break;
	}
}
void UIElement::setMargins(sf::Vector2i vector, sf::Sprite& sprite) {
	sf::Vector2f _sprite_position = sprite.getPosition();
	sprite.setPosition(_sprite_position.x + vector.x, _sprite_position.y + vector.y);
};