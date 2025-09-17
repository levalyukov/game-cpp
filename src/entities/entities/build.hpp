#pragma once

#include "../entity.hpp"

#include <iostream>

class Build : public Entity {
	public:
		inline Build(
			sf::Texture* texture,
			sf::Vector2f position,
			sf::Vector2i frame_size
		) : build_texture(std::move(*texture)),
			build_position(position),
			build_size(frame_size) {
			sprite->setTexture(build_texture);
			sprite->setTextureRect(sf::IntRect({ 0,0 }, frame_size));
			sprite->setScale({ 4,4 });
			sprite->setPosition(build_position);
		};

		std::function<void()> handler;
		inline sf::Sprite& getSprite() const { return *sprite; };
		inline float getDepth() const override  { return sprite->getPosition().y; };
		inline void setHandleEvent(std::function<void()> new_handler) override { handler = new_handler; };
		void handleEvent(sf::RenderWindow& window, sf::Event& event) override;
		inline void render(sf::RenderWindow& window, float delta_time, sf::View& game_camera, sf::Clock& clock) override { window.draw(*sprite); };

	private:
		std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();
		sf::Texture& build_texture;
		sf::Vector2f build_position;
		sf::Vector2i build_size;

		enum MouseState {Normal, Hovered, Pressed};
		MouseState m_state = Normal;
		bool isPressed = false;
};