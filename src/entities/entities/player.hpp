#pragma once

#include "../entity.hpp"
#include "../../core/animations/animations.hpp"
#include "../../core/globals.hpp"

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
			player->setTexture(idle);
			player->setTextureRect(sf::IntRect(16, 0, spriteSizeX.x, spriteSizeX.y));
			player->setScale(4, 4);
			shadow_sprite.setTexture(shadow_texture);
			shadow_sprite.setScale(4, 4);
		};

		void movement(float deltaTime);
		inline void setStoppedFlag(bool _state) { stopped_flag = _state; };
		inline bool getStoppedFlag() const { return stopped_flag; };
		inline sf::Sprite& getSprite() const { return *player; };
		inline float getDepth() const override { return player->getPosition().y + 4; };
		inline void setEvent(std::function<void()> new_event) override {};
		inline void setHandler(std::function<void()> new_handler) override {};
		inline void event(sf::RenderWindow& window, sf::Event& event) override {};
		inline void handler(sf::RenderWindow& window, sf::Event& event) override {};
		void render(sf::RenderWindow& window, float delta, sf::View& gameCamera, sf::Clock& clock) override;
	
	private:
		std::unique_ptr<sf::Sprite> player = std::make_unique<sf::Sprite>();
		sf::Sprite shadow_sprite;

		sf::Texture idle;
		sf::Texture walkHorizontal;
		sf::Texture walkVertical;
		sf::Texture shadow_texture;
		sf::Vector2i spriteSizeX {16,16};

		AnimationManager anim;
		std::string direction;
		std::string currentDirection;
		std::string oldDirection;

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

		bool stopped_flag = false;
};