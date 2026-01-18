#pragma once
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Graphics.hpp>

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH  480
#define WINDOW_TITLE  ""
#define WINDOW_ICON   ""

class Engine {
  public:
    Engine(void) {
      event = std::make_unique<sf::Event>();
      window = std::make_unique<sf::Window>(
      sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), WINDOW_TITLE);
      if (window) {
        window->setFramerateLimit(60);
        if (icon.loadFromFile(WINDOW_ICON)) {
          iconPixels = icon.getPixelsPtr();
          window->setIcon(icon.getSize().x, icon.getSize().y, iconPixels);
        };
      };
    };

    inline sf::Window* getGameWindow(void) const { return window.get(); };
    inline sf::Event* getGameEvent(void) const { return event.get(); };
  private:
    std::unique_ptr<sf::Window> window = nullptr;
    std::unique_ptr<sf::Event> event = nullptr;
    const sf::Uint8* iconPixels = {};
    sf::Image icon;
};

#endif