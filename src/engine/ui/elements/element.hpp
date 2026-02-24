#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>

class UIElement {
	public:
    virtual void update(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void setDepth(const int16_t new_depth) = 0;
    virtual int16_t getDepth(void) const = 0;
    virtual bool getVisible(void) const = 0;
    virtual void setVisible(const bool& new_state) = 0;
};