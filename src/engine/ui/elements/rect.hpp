#pragma once

#include <memory>
#include "element.hpp"

class Rect : public UIElement {
  public:
    Rect(
      const sf::Color& color,
      const sf::Vector2f& size
    ) {
      if (!rect) rect = std::make_unique<sf::RectangleShape>();
      rect->setFillColor(color);
      rect->setSize(size);
    };

    inline sf::RectangleShape& getRect(void) { return *rect.get(); };
    inline void setDepth(const int16_t new_depth) override { depth = new_depth; };
    inline int16_t getDepth(void) const override { return depth; };
    inline bool getVisible(void) const override { return visible; };
    inline void setVisible(const bool& new_state) override { visible = new_state; };
    inline void update(sf::RenderWindow& window, sf::Event& event) override { if (rect) window.draw(*rect); };

  private:
    int16_t depth = 0;
    bool visible = true;
    std::unique_ptr<sf::RectangleShape> rect = nullptr;
};