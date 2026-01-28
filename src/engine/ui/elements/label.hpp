#pragma once

#include "element.hpp"

class Label : public UIElement {
  public:
    Label(
      std::wstring& message,
      sf::Font* label_font
    ) : font(*label_font) {
      if (!text) text = std::make_unique<sf::Text>();
      text->setString(message);
      text->setFont(font);
    };

    inline void update(sf::RenderWindow& window, sf::Event& event) { window.draw(*text); };
    inline void setDepth(const int16_t new_depth) { depth = new_depth; };
    inline int16_t getDepth(void) const { return depth; };

  private:
    int16_t depth = 0;
    sf::Font& font;
    std::unique_ptr<sf::Text> text = nullptr;
};