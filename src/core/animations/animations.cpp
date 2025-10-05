#include "animations.hpp"

void AnimationManager::update(
	sf::Sprite& sprite,
	sf::Texture& texture,
	sf::Vector2i animation_start,
	sf::Vector2i sprite_size,
	const float frame_duration,
	const int max_frames,
	const float delta
) {
	animTimer += delta;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(
		animationVector.x, animation_start.y,
		sprite_size.x, sprite_size.y
	));

	printf("Delta: %f | animTimer: %f | frame_duration: %f\n", delta, animTimer, frame_duration);

	if (animTimer > frame_duration) {
		printf("Frame a changed!");
		animTimer = 0.0;
		animationVector.x += 16;
		if (animationVector.x > sprite_size.x * max_frames) animationVector.x = 0;
		sprite.setTextureRect(sf::IntRect(
			animationVector.x, animation_start.y,
			sprite_size.x, sprite_size.y
		));
	};
};