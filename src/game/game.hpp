#pragma once
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <engine.hpp>
#include <ui/ui-manager.hpp>
#include <entity/entity-manager.hpp>
#include <levels/level-manager.hpp>
#include <events/event-manager.hpp>

class Game {
  public:
    Game(void) {
      run();
    };

  private:
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    sf::RenderWindow& window = *engine->getGameWindow();
    sf::Event& event = *engine->getGameEvent();

    inline void run(void) {
      if (engine) {
        init();
        game();
      };
    };

    std::unique_ptr<LevelManager> level = std::make_unique<LevelManager>();

    void init(void);
    inline void game(void) {
      while (window.isOpen()) {
        engine->windowEvent();
        if (level) level->update(window, event);
      };
    };
};

#endif