#pragma once

#include <levels/level.hpp>

class GameMap1 : public Level {
  public:
    inline void update(sf::RenderWindow& window, sf::Event& event) override {
      window.clear(sf::Color(255, 105, 180));
      window.display();
    };
};