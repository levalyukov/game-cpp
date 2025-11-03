#pragma once

#include "../entity.hpp"
#include "../../core/animations/animations.hpp"

#include <stdint.h>
#include <memory>

class NPC : public Entity {
	public:
		NPC(
			sf::Texture*&& idle_texture,
			sf::Texture*&& movement_vertical,
			sf::Texture*&& movement_horizontal,
			sf::Texture*&& shadow_texture
		) : idleTexture(std::move(*idle_texture)),
			movementVertical(std::move(*movement_vertical)),
			movementHorizontal(std::move(*movement_horizontal)),
			shadowTexture(std::move(*shadow_texture)) {
			sprite = std::make_unique<sf::Sprite>();
			sprite->setTexture(idleTexture);
			sprite->setTextureRect(sf::IntRect({ 16,0 }, { 16,16 }));
			sprite->setScale({ 4,4 });
			shadow = std::make_unique<sf::Sprite>();
			shadow->setTexture(shadowTexture);
			shadow->setScale({ 4,4 });
		};

		inline void setOrder(uint8_t new_order) { order = new_order; };
		inline uint8_t getOrder() const { return order; };
		inline AnimationManager& getAnimation() { return anim; };
		inline sf::Sprite& getSprite() const { return *sprite; };

		inline float getDelta() const override { return deltaSaved; };
		inline float getDepth() const override { return sprite->getPosition().y + 4; };
		inline sf::Texture& getTextureIDLE() const override  { return idleTexture; };
		inline sf::Texture& getTextureMoveVertical() const override { return movementVertical; };
		inline sf::Texture& getTextureMoveHorizontal() const override { return movementHorizontal; };
		inline void setEvent(std::function<void()> new_event) override { event_ = new_event; };
		inline void setHandler(std::function<void()> new_handler) override { handler_ = new_handler; };
		inline void event(sf::RenderWindow& window, sf::Event& event) override { if (event_) event_(); };
		void handler(sf::RenderWindow& window, sf::Event& event) override;
		void render(sf::RenderWindow& window, float delta, sf::View& game_camera, sf::Clock& clock) override;
	
	private:
		AnimationManager anim;
		enum MouseState { Normal, Hovered, Pressed };
		MouseState mouseState = Normal;

		std::function<void()> handler_;
		std::function<void()> event_;

		std::unique_ptr<sf::Sprite> sprite = nullptr;
		std::unique_ptr<sf::Sprite> shadow = nullptr;
		sf::Texture&& idleTexture;
		sf::Texture&& movementVertical;
		sf::Texture&& movementHorizontal;
		sf::Texture&& shadowTexture;

		uint8_t order = 0;

		bool isPressed = false;
		bool isDeltaSaved = false;
		float deltaSaved = 0.0f;
};