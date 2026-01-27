#pragma once
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <engine.hpp>
#include <scenes/scene-manager.hpp>

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

    std::unique_ptr<SceneManager> scene = std::make_unique<SceneManager>();

    void init(void);
    inline void game(void) {
      while (window.isOpen()) {
        engine->windowEvent();
        if (scene) scene->update(window, event);
      };
    };
};

#endif