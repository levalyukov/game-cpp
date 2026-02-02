#include "ui-manager.hpp"

void UIManager::setElementPosition(
  sf::RenderWindow& window,
  sf::Sprite& sprite, 
  const UIManager::UIPosition position, 
  const sf::Vector2i margin
) {
  const int windowWidth = window.getSize().x;
  const int windowHeight = window.getSize().y;

  const double spriteX = sprite.getPosition().x;
  const double spriteY = sprite.getPosition().y;
  const int spriteHeight = sprite.getGlobalBounds().height;
  const int spriteWidth = sprite.getGlobalBounds().width;
  int newPositionX = 0, newPositionY = 0;

  switch (position) {
    case UIManager::UIPosition::TopLeft:
      newPositionX = 0 + margin.x;
      newPositionY = 0 + margin.y;
      sprite.setPosition(
        newPositionX, 
        newPositionY
      );break;
  
    case UIManager::UIPosition::TopCenter:
      newPositionX = ((windowWidth - spriteWidth) / 2) + margin.x;
      newPositionY = 0 + margin.y;
      sprite.setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::TopRight:
      newPositionX = (windowWidth - spriteWidth) - margin.x;
      newPositionY = 0 + margin.y;
      sprite.setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::MiddleLeft:
      newPositionX = 0 + margin.x;
      newPositionY = ((windowWidth - spriteWidth) / 2) + margin.y;
      sprite.setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::MiddleCenter:
      newPositionX = ((windowWidth - spriteWidth) / 2) + margin.x;
      newPositionY = ((windowHeight - spriteHeight) / 2) + margin.y;
      sprite.setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::MiddleRight:
      newPositionX = (windowWidth - spriteWidth) - margin.x;
      newPositionY = ((windowHeight - spriteHeight) / 2) + margin.y;
      sprite.setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::BottomLeft:
      newPositionX = 0;
      newPositionY = windowHeight - spriteHeight - margin.y;
      sprite.setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::BottomCenter:
      newPositionX = ((windowWidth - spriteWidth) / 2) + margin.x;
      newPositionY = windowHeight - spriteHeight - margin.y;
      sprite.setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::BottomRight:
      newPositionX = (windowWidth - spriteWidth) - margin.x;
      newPositionY = windowHeight - spriteHeight - margin.y;
      sprite.setPosition(
        newPositionX,
        newPositionY
      ); break;

    default: break;
  };

  #if defined(DEBUG)
  LOGO("New position of the sprite (height %i, width %i): (x: %i, y: %i)",
    spriteHeight, spriteWidth, newPositionX, newPositionY);
  #endif
};
void UIManager::setLabelPosition(const sf::Sprite& parent, const Label& label,
  UIManager::UIPosition position, const sf::Vector2i margin) {
  const int parentX = parent.getPosition().x;
  const int parentY = parent.getPosition().y;
  const int parentHeight = parent.getGlobalBounds().height;
  const int parentWidth = parent.getGlobalBounds().width;

  const sf::Text& text = label.getLabel();
  const int labelX = text.getPosition().x;
  const int labelY = text.getPosition().y;
  const int labelHeight = text.getGlobalBounds().height;
  const int labelWidth = text.getGlobalBounds().width;
  const int labelSize = text.getCharacterSize();

  int newPositionX = 0, newPositionY = 0;

  switch (position) {
    case UIManager::UIPosition::TopLeft:
      newPositionX = parentX + margin.x;
      newPositionY = parentY + margin.y;
      label.getLabel().setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::TopCenter:
      newPositionX = (parentX + ((parentWidth - labelWidth) / 2)) + margin.x;
      newPositionY = parentY + margin.y;
      label.getLabel().setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::TopRight:
      newPositionX = parentX + ((parentWidth - labelWidth)) + margin.x;
      newPositionY = parentY + margin.y;
      label.getLabel().setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::MiddleLeft:
      newPositionX = parentX + margin.x;
      newPositionY = parentY + ((parentHeight - labelHeight) / 2) + margin.y;
      label.getLabel().setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::MiddleCenter:
      newPositionX = parentX + ((parentWidth - labelWidth) / 2) + margin.x;
      newPositionY = parentY + ((parentHeight - labelHeight) / 2) + margin.y;
      label.getLabel().setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::MiddleRight:
      newPositionX = parentX + ((parentWidth - labelWidth)) + margin.x;
      newPositionY = parentY + ((parentHeight - labelHeight) / 2) + margin.y;
      label.getLabel().setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::BottomLeft:
      newPositionX = parentX + margin.x;
      newPositionY = parentY + ((parentHeight - labelHeight)) + margin.y;
      label.getLabel().setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::BottomCenter:
      newPositionX = parentX + ((parentWidth - labelWidth) / 2) + margin.x;
      newPositionY = parentY + ((parentHeight - labelHeight)) + margin.y;
      label.getLabel().setPosition(
        newPositionX,
        newPositionY
      ); break;

    case UIManager::UIPosition::BottomRight:
      newPositionX = parentX + ((parentWidth - labelWidth)) + margin.x;
      newPositionY = parentY + ((parentHeight - labelHeight)) + margin.y;
      label.getLabel().setPosition(
        newPositionX,
        newPositionY
      ); break;

    default: break;
  };
};