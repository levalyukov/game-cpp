#include "game.hpp"
#include "maps/level1.hpp"

void Game::init(void) {
  if (level->addLevel("level1", std::make_unique<GameMap1>(level.get()))) {
    level->setLevel("level1");
  };
};