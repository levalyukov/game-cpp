#include "ui-manager.hpp"

void UIManager::setElementPosition(
  sf::RenderWindow& window,
  sf::Sprite& sprite, 
  const UIManager::UIPosition position, 
  const sf::Vector2i margin
) {
  const int windowWidth = window.getSize().x;
  const int windowHeight = window.getSize().y;

  double spriteX = sprite.getPosition().x;
  double spriteY = sprite.getPosition().y;
  int spriteHeight = sprite.getGlobalBounds().height;
  int spriteWidth = sprite.getGlobalBounds().width;
  int newPositionX = 0;
  int newPositionY = 0;

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