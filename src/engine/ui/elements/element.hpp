#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>

class UIElement {
	public:
    virtual void update(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual uint8_t getDepth(void) const = 0;
};