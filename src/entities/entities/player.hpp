#pragma once

#include <memory>
#include "../entity.hpp"
#include "../../core/animations/animations.hpp"
#include "../../core/globals.hpp"
#include "../../mechanics/items.hpp"

class Player : public Entity {
	public:
		Player(
			sf::Texture*&& character_idle,
			sf::Texture*&& character_walk_horizontal,
			sf::Texture*&& character_walk_vertical,
			sf::Texture*&& character_item_idle,
			sf::Texture*&& character_item_horizontal,
			sf::Texture*&& character_item_vertical,
			sf::Texture*&& character_shadow
		) : idle(std::move(*character_idle)),
			movementHorizontal(std::move(*character_walk_horizontal)),
			movementVertical(std::move(*character_walk_vertical)),
			itemIdle(std::move(*character_item_idle)),
			movementItemHorizontal(std::move(*character_item_horizontal)),
			movementItemVertical(std::move(*character_item_vertical)),
			shadowTexture(std::move(*character_shadow)) {
			player = std::make_unique<sf::Sprite>();
			player->setTexture(idle);
			player->setTextureRect(sf::IntRect(16, 0, spriteSize.x, spriteSize.y));
			player->setPosition({ (25 * 64) / 2,(17 * 64) / 2 });
			player->setScale(4, 4);
			shadowSprite.setTexture(shadowTexture);
			shadowSprite.setScale(4, 4);
		};

		void movement(float deltaTime);
		void setSelectedItem(uint8_t new_item, Items& items);
		inline uint8_t getSelectedItem() const { return selectedItem; };
		inline sf::Texture& getTextureIDLE() const { return idle; };
		inline sf::Texture& getTextureMoveVertical() const { return movementVertical; };
		inline sf::Texture& getTextureMoveHorizontal() const { return movementHorizontal; };
		inline float getDelta() const { return savedDelta; };
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
		sf::Vector2i spriteSize{ 16,16 };
		std::unique_ptr<sf::Sprite> player = nullptr;
		std::unique_ptr<sf::Sprite> itemSprite = nullptr;
		std::unique_ptr<sf::Texture> itemTexture = nullptr;
		sf::Sprite shadowSprite;

		sf::Texture& idle;
		sf::Texture& movementHorizontal;
		sf::Texture& movementVertical;
		sf::Texture& shadowTexture;

		sf::Texture& itemIdle;
		sf::Texture& movementItemHorizontal;
		sf::Texture& movementItemVertical;

		AnimationManager anim;
		std::string direction;
		std::string currentDirection;
		std::string oldDirection;

		uint8_t selectedItem = 0;
		uint8_t currentFrame = 0;
		float animationTimer = 0.0f;
		float savedDelta = 0.f;

		sf::Vector2i vectorUP = { 0,16 };
		sf::Vector2i vectorDOWN = { 0,0 };
		sf::Vector2i vectorLEFT = { 0,0 };
		sf::Vector2i vectorRIGHT = { 0,16 };

		sf::Vector2i oldVectorUP;
		sf::Vector2i oldVectorDOWN;
		sf::Vector2i oldVectorLEFT;
		sf::Vector2i oldVectorRIGHT;

		bool isDeltaSaved = false;
		bool stopped_flag = false;
};