#include "game.hpp"
#include "maps/level1.hpp"

void Game::init(void) {
  if (scene->addScene("level1", std::make_unique<GameMap1>(scene.get()))) {
    scene->setScene("level1");
  };
};