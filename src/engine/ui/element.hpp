#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>

class UIElement {
	public:
    virtual void update(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void setDepth(const uint8_t depth) = 0;
    virtual uint8_t getDepth(void) const = 0;
};