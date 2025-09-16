#pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
class Animations {
	public:
		void setAnimation(
            sf::Sprite& sprite,
            sf::Texture& texture,
            sf::Vector2i& anim_start,
            int frame_count,
            sf::Vector2i frames,
            float& timer,
            float frame_duration,
            float delta
		);
};

