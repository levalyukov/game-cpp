#pragma once

#include <SFML/Graphics.hpp>

class Level {
  public:
    virtual void update(sf::RenderWindow& window, sf::Event& event) = 0;
};