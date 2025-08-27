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

void UIElement::setRelativePosition(
	enum ElementPosition current_position, 
	sf::Sprite& parent_sprite,
	sf::Sprite& child_sprite,
	sf::Vector2f margins
) {
	float parentX = static_cast<float>(parent_sprite.getPosition().x);
	float parentY = static_cast<float>(parent_sprite.getPosition().y);
	float parentBoundsWidth = static_cast<float>(parent_sprite.getGlobalBounds().width);
	float parentBoundsHeight = static_cast<float>(parent_sprite.getGlobalBounds().height);
	float childBoundsWidth = static_cast<float>(child_sprite.getGlobalBounds().width);
	float childBoundsHeight = static_cast<float>(child_sprite.getGlobalBounds().height);

	switch (current_position) {
		case TopLeft: 
			child_sprite.setPosition(parentX + margins.x, parentY + margins.y);
			break;
		case TopCenter:
			child_sprite.setPosition(parentX + (parentBoundsWidth - childBoundsWidth) / 2.f + margins.x, parentY + margins.y);
			break;
		case TopRight:
			child_sprite.setPosition({ parentX + (parentBoundsWidth - childBoundsWidth) + margins.x,parentY + margins.y });
			break;
		
		case MiddleLeft:
			child_sprite.setPosition({ parentX + margins.x, parentY + (parentBoundsHeight - childBoundsHeight) / 2.f + margins.y });
			break;
		case MiddleCenter:
			child_sprite.setPosition({ parentX + (parentBoundsWidth - childBoundsWidth) / 2.f + margins.x, parentY + (parentBoundsHeight - childBoundsHeight) / 2.f + margins.y });
			break;
		case MiddleRight:
			child_sprite.setPosition({ parentX + (parentBoundsWidth - childBoundsWidth) + margins.x, parentY + (parentBoundsHeight - childBoundsHeight) / 2.f + margins.y });
			break;

		case BottomLeft:
			child_sprite.setPosition({ parentX + margins.x, parentY + (parentBoundsHeight - childBoundsHeight) + margins.y });
			break;
		case BottomCenter:
			child_sprite.setPosition({ parentX + (parentBoundsWidth - childBoundsWidth) / 2.f + margins.x, parentY + (parentBoundsHeight - childBoundsHeight) + margins.y });
			break;
		case BottomRight:
			child_sprite.setPosition({ parentX + (parentBoundsWidth - childBoundsWidth) + margins.x, parentY + (parentBoundsHeight - childBoundsHeight) + margins.y });
			break;
	}
}