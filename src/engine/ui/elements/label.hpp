#pragma once

#include "element.hpp"
#include <stdint.h>

class Label : public UIElement {
  public:
    Label(
      const std::wstring& message,
      sf::Font* label_font,
      const uint16_t size = 20,
      const sf::Color& color = sf::Color::White
    ) : font(*label_font) {
      if (!text) text = std::make_unique<sf::Text>();
      text->setFont(font);
      text->setString(message);
      text->setCharacterSize(size);
    };

    inline sf::Text& getLabel(void) const { return *text.get(); };
    inline void update(sf::RenderWindow& window, sf::Event& event) { window.draw(*text); };
    inline void setDepth(const int16_t new_depth) { depth = new_depth; };
    inline int16_t getDepth(void) const { return depth; };

  private:
    int16_t depth = 0;
    sf::Font& font;
    std::unique_ptr<sf::Text> text = nullptr;
};