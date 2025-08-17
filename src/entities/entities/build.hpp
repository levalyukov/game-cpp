#pragma once

#include "../entity.hpp"

class Build : public Entity {
	public:
		Build(
			sf::Texture* texture,
			sf::Vector2f position,
			sf::Vector2i frame_size
		) : build_texture(std::move(*texture)),
			build_position(position),
			build_size(frame_size) {
			build_sprite.setTexture(build_texture);
			build_sprite.setTextureRect(sf::IntRect({ 0,0 }, frame_size));
			build_sprite.setScale({ 4,4 });
			build_sprite.setPosition(build_position);
		};

		std::function<void()> handler;
		inline float getDepth() const override  { return build_sprite.getPosition().y; };
		inline void setHandleEvent(std::function<void()> new_handler) override { handler = new_handler; };
		void handleEvent(sf::RenderWindow& window, sf::Event& event) override;
		inline void render(sf::RenderWindow& window, float deltaTime, sf::View& gameCamera, sf::Clock& clock) override { window.draw(build_sprite); };

	private:
		sf::Sprite build_sprite;
		sf::Texture& build_texture;
		sf::Vector2f build_position;
		sf::Vector2i build_size;
};