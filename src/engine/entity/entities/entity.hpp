#pragma once

#include <SFML/Graphics.hpp>

class Entity {
  public:
    virtual void update(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual sf::Sprite& getSprite(void) const = 0;
};