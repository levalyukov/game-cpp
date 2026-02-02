#include "game.hpp"

#include "maps/menu.hpp"
#include "maps/level1.hpp"

void Game::init(void) {
  if (scene->addScene("main-menu",
    std::make_unique<MainMenu>(window, event, scene.get()))) {
    scene->setPointer("main-menu");
  };

  scene->addScene("level1", 
    std::make_unique<Level1>(
      window, event, scene.get()));
};