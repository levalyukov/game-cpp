#pragma once

#include "../entity.hpp"
#include "../../core/animations/animations.hpp"

#include <SFML/Graphics.hpp>

class Player : public Entity {
	public:
		Player(
			sf::Texture* character_idle,
			sf::Texture* character_walk_horizontal,
			sf::Texture* character_walk_vertical,
			sf::Texture* character_shadow
		) : idle(std::move(*character_idle)),
			walkHorizontal(std::move(*character_walk_horizontal)),
			walkVertical(std::move(*character_walk_vertical)),
			shadow_texture(std::move(*character_shadow)) {
			player.setTexture(idle);
			player.setTextureRect(sf::IntRect(16, 0, spriteSizeX.x, spriteSizeX.y));
			player.setPosition((9 / 2) * 64, (9 / 2) * 64);
			player.setScale(4, 4);
			shadow_sprite.setTexture(shadow_texture);
			shadow_sprite.setScale(4, 4);
			player.setPosition({ 51 * 16,52 * 16 });
		};

		void movement(float deltaTime);
		void handleEvent(sf::RenderWindow& window, sf::Event& event) override {};
		void render(sf::RenderWindow& window, float deltaTime, sf::View& gameCamera, sf::Clock& clock) override;

	private:
		sf::Sprite player;
		sf::Sprite shadow_sprite;

		sf::Texture idle;
		sf::Texture walkHorizontal;
		sf::Texture walkVertical;
		sf::Texture shadow_texture;

		sf::Vector2i spriteSizeX {16,16};

		const float RUN_SPEED = 6.0f;
		const float WALK_SPEED = 4.0f;

		Animations animations;

		std::string direction;
		std::string currentDirection;
		std::string oldDirection;

		const float RUN_ANIM = 0.10f;
		const float WALK_ANIM = 0.15f;

		int currentFrame = 0;
		float animationTimer = 0.0f;

		sf::Vector2i vectorUP = { 0,16 };
		sf::Vector2i vectorDOWN = { 0,0 };
		sf::Vector2i vectorLEFT = { 0,0 };
		sf::Vector2i vectorRIGHT = { 0,16 };

		sf::Vector2i oldVectorUP;
		sf::Vector2i oldVectorDOWN;
		sf::Vector2i oldVectorLEFT;
		sf::Vector2i oldVectorRIGHT;
};