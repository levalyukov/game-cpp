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
    sf::RenderWindow& window = *engine->getGameWindow();
    sf::Event& event = *engine->getGameEvent();

    inline void run(void) {
      if (!engine) return;
      game();
    };

    std::unique_ptr<UIManager> ui = std::make_unique<UIManager>();
    std::unique_ptr<LevelManager> level = std::make_unique<LevelManager>();
    std::unique_ptr<EntityManager> entity = std::make_unique<EntityManager>();
    inline void game(void) {
      while (window.isOpen()) {
        engine->windowEvent();
        if (ui) ui->update();
        if (entity) entity->update(window, event);
        if (level) level->update();
      };
    };
};

#endif