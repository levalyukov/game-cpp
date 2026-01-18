#pragma once
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <engine.hpp>
#include <ui/ui-manager.hpp>
#include <entity/entity-manager.hpp>
#include <levels/level-manager.hpp>

class Game {
  public:
    Game(void) {
      run();
    };

  private:
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    sf::Window& window = *engine->getGameWindow();
    sf::Event& event = *engine->getGameEvent();

    inline void run(void) {
      if (!engine) return;
      game();
    };

    inline void game(void) {
      while (window.isOpen()) {
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed) window.close();
        };
      };
    };
};

#endif