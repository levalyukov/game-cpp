#pragma once
#ifndef MIREN
#define MIREN

#include <SFML/Graphics.hpp>

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH  640
#define WINDOW_TITLE  ""
#define WINDOW_ICON   ""

class Engine {
  public:
    Engine(void) {
      event = std::make_unique<sf::Event>();
      window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
      if (window) {
        window->setFramerateLimit(60);
        if (icon.loadFromFile(WINDOW_ICON)) {
          iconPixels = icon.getPixelsPtr();
          window->setIcon(icon.getSize().x, icon.getSize().y, iconPixels);
        };
      };
    }; ~Engine(void) = default;

    inline sf::RenderWindow* getGameWindow(void) const { return window.get(); };
    inline sf::Event* getGameEvent(void) const { return event.get(); };
    inline void windowEvent(void) {
      while (window->pollEvent(*event)) 
        if (event->type == sf::Event::Closed) window->close();
    };

  private:
    std::unique_ptr<sf::RenderWindow> window = nullptr;
    std::unique_ptr<sf::Event> event = nullptr;
    const sf::Uint8* iconPixels = {};
    sf::Image icon;
};

#endif