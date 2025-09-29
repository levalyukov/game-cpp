#include "ui-element.hpp"

void UIElement::setGlobalPosition(
	enum ElementPosition position, 
	sf::Sprite& sprite,
	sf::Vector2f margins
) {
	sf::RenderWindow& window = Globals::instance().getWindow();
	float windowSizeX = static_cast<float>(window.getSize().x);
	float windowSizeY = static_cast<float>(window.getSize().y);
	float spriteSizeWidth = static_cast<float>(sprite.getGlobalBounds().width);
	float spriteSizeHeight = static_cast<float>(sprite.getGlobalBounds().height);

	switch (position) {
		case TopLeft:
			sprite.setPosition({ 0,0 });
			break;
		case TopCenter:
			sprite.setPosition({ (windowSizeX - spriteSizeWidth) / 2.f + margins.x, 0 + margins.y });
			break;
		case TopRight:
			sprite.setPosition({ windowSizeX - spriteSizeWidth + margins.x, 0 + margins.y });
			break;

		case MiddleLeft:
			sprite.setPosition({ 0 + margins.x, (windowSizeY - spriteSizeHeight) / 2.f + margins.y });
			break;
		case MiddleCenter:
			sprite.setPosition({ (windowSizeX - spriteSizeWidth) / 2.f + margins.x, (windowSizeY - spriteSizeHeight) / 2.f + margins.y });
			break;
		case MiddleRight:
			sprite.setPosition({ windowSizeX - spriteSizeWidth + margins.x, (windowSizeY - spriteSizeHeight) / 2.f + margins.y });
			break;

		case BottomLeft:
			sprite.setPosition({ 0 + margins.x, windowSizeY - spriteSizeHeight + margins.y });
			break;
		case BottomCenter:
			sprite.setPosition({ (windowSizeX - spriteSizeWidth) / 2.f + margins.x, windowSizeY - spriteSizeHeight + margins.y });
			break;
		case BottomRight:
			sprite.setPosition({ windowSizeX - spriteSizeWidth + margins.x, windowSizeY - spriteSizeHeight + margins.y });
			break;
	};
};

void UIElement::setRelativePosition(
	enum ElementPosition position, 
	sf::Sprite& parent,
	sf::Sprite& child,
	sf::Vector2f margins
) {
	float parentX = static_cast<float>(parent.getPosition().x);
	float parentY = static_cast<float>(parent.getPosition().y);
	float parentWidth = static_cast<float>(parent.getGlobalBounds().width);
	float parentHeight = static_cast<float>(parent.getGlobalBounds().height);
	float childWidth = static_cast<float>(child.getGlobalBounds().width);
	float childHeight = static_cast<float>(child.getGlobalBounds().height);

	switch (position) {
		case TopLeft: 
			child.setPosition(parentX + margins.x, parentY + margins.y);
			break;
		case TopCenter:
			child.setPosition(parentX + (parentWidth - childWidth) / 2.f + margins.x, parentY + margins.y);
			break;
		case TopRight:
			child.setPosition({ parentX + (parentWidth - childWidth) + margins.x,parentY + margins.y });
			break;
		
		case MiddleLeft:
			child.setPosition({ parentX + margins.x, parentY + (parentHeight - childHeight) / 2.f + margins.y });
			break;
		case MiddleCenter:
			child.setPosition({ parentX + (parentWidth - childWidth) / 2.f + margins.x, parentY + (parentHeight - childHeight) / 2.f + margins.y });
			break;
		case MiddleRight:
			child.setPosition({ parentX + (parentWidth - childWidth) + margins.x, parentY + (parentHeight - childHeight) / 2.f + margins.y });
			break;

		case BottomLeft:
			child.setPosition({ parentX + margins.x, parentY + (parentHeight - childHeight) + margins.y });
			break;
		case BottomCenter:
			child.setPosition({ parentX + (parentWidth - childWidth) / 2.f + margins.x, parentY + (parentHeight - childHeight) + margins.y });
			break;
		case BottomRight:
			child.setPosition({ parentX + (parentWidth - childWidth) + margins.x, parentY + (parentHeight - childHeight) + margins.y });
			break;
	};
};

void UIElement::setGlobalPositionText(
	enum ElementPosition position,
	sf::Text& text,
	sf::Vector2f margins
) {
	sf::RenderWindow& window = Globals::instance().getWindow();
	float windowX = static_cast<float>(window.getSize().x);
	float windowY = static_cast<float>(window.getSize().y);
	float textHeight = text.getGlobalBounds().height;
	float textWidth = text.getGlobalBounds().width;
	switch (position) {
	case TopLeft:
		text.setPosition({ 0 + margins.x,0 + margins.y });
		break;
	case TopCenter:
		text.setPosition({ (windowX - textWidth) / 2.f + margins.x, 0 + margins.y });
		break;
	case TopRight:
		text.setPosition({ windowX - textWidth + margins.x, 0 + margins.y });
		break;

	case MiddleLeft:
		text.setPosition({ 0 + margins.x, (windowY - textHeight) / 2.f + margins.y });
		break;
	case MiddleCenter:
		text.setPosition({ (windowX - textWidth) / 2.f + margins.x, (windowY - textHeight) / 2.f + margins.y });
		break;
	case MiddleRight:
		text.setPosition({ windowX - textWidth + margins.x, (windowY - textHeight) / 2.f + margins.y });
		break;

	case BottomLeft:
		text.setPosition({ 0 + margins.x, (windowY - textHeight) + margins.y });
		break;
	case BottomCenter:
		text.setPosition({ (windowX - textWidth) / 2.f + margins.x, (windowY - textHeight) + margins.y });
		break;
	case BottomRight:
		text.setPosition({ (windowX - textWidth) + margins.x, (windowY - textHeight) + margins.y });
		break;
	};
};

/*? This function incorrectly assigns a position to the text. idk */
/*? p.s. maybe because i forgot about the font size...? */

void UIElement::setRelativePositionText(
	enum ElementPosition position, 
	sf::Sprite& parent, 
	sf::Text& child,
	sf::Vector2f margins
) {
	float parentX = static_cast<float>(parent.getPosition().x);
	float parentY = static_cast<float>(parent.getPosition().y);
	float parentWidth = static_cast<float>(parent.getGlobalBounds().width);
	float parentHeight = static_cast<float>(parent.getGlobalBounds().height);
	float childWidth = static_cast<float>(child.getGlobalBounds().width);
	float childHeight = static_cast<float>(child.getGlobalBounds().height);

	switch (position) {
		case TopLeft:
			child.setPosition({ parentX + margins.x,parentY + margins.y });
			break;
		case TopCenter:
			child.setPosition({ parentX + (parentWidth - childWidth) / 2.f + margins.x,parentY + margins.y });
			break;
		case TopRight:
			child.setPosition({ parentX + (parentWidth - childWidth) + margins.x,parentY + margins.y });
			break;

		case MiddleLeft:
			child.setPosition({ parentX + margins.x,parentY + (parentHeight - childHeight) / 2.f + margins.y });
			break;
		case MiddleCenter:
			child.setPosition({ parentX + (parentWidth - childWidth) / 2.f + margins.x,parentY + (parentHeight - childHeight) / 2.f + margins.y });
			break;
		case MiddleRight:
			child.setPosition({ parentX + (parentWidth - childWidth) + margins.x,parentY + (parentHeight - childHeight) / 2.f + margins.y });
			break;

		case BottomLeft:
			child.setPosition({ parentX + margins.x, parentY + (parentHeight - childHeight) + margins.y });
			break;
		case BottomCenter:
			child.setPosition({ parentX + (parentWidth - childWidth) / 2.f + margins.x ,parentY + (parentHeight - childHeight) + margins.y });
			break;
		case BottomRight:
			child.setPosition({ parentX + (parentWidth - childWidth) + margins.x ,parentY + (parentHeight - childHeight) + margins.y });
			break;
	};
};