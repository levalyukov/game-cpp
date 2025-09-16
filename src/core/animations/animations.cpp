#include "animations.hpp"

void Animations::setAnimation(
    sf::Sprite& sprite,
    sf::Texture& texture,
    sf::Vector2i& anim_start,
    int frame_count,
    sf::Vector2i frames,
    float& timer,
    float frame_duration,
    float delta
) {
    timer += delta;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(anim_start.x, anim_start.y, frames.x, frames.y));
    if (timer >= frame_duration) {
        timer = 0;
        anim_start.x += frames.x;
        if (anim_start.x >= frames.x * frame_count) anim_start.x = 0;
        sprite.setTextureRect(sf::IntRect(anim_start.x, anim_start.y, frames.x, frames.y));
    }
}