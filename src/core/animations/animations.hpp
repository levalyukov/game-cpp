#pragma once

#include <SFML/Graphics.hpp>

class AnimationManager {
	public:
		void update(
			sf::Sprite& sprite, sf::Texture& texture, sf::Vector2i animation_start, 
			sf::Vector2i sprite_size, const float frame_duration, const int max_frames, 
			const float delta
		);

	private:
		float animTimer = 0.0f;
		sf::Vector2i animationVector = { 0,0 };
};

