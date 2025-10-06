#pragma once

#include "../entity.hpp"

class NPC : public Entity {
	public:
		NPC(
			sf::Texture* idle_texture,
			sf::Texture* movement_vertical,
			sf::Texture* movement_horizontal,
			sf::Texture* shadow_texture
		) : idleTexture(std::move(*idle_texture)),
			movementVertical(std::move(*movement_vertical)),
			movementHorizontal(std::move(*movement_horizontal)),
			shadowTexture(std::move(*shadow_texture)) {
			sprite->setTexture(idleTexture);
			sprite->setTextureRect(sf::IntRect({ 16,0 }, { 16,16 }));
			sprite->setScale({ 4,4 });
			shadow.setTexture(shadowTexture);
			shadow.setScale({ 4,4 });
		};

		std::function<void()> handler_;
		std::function<void()> event_;
		inline float getDelta() const { return deltaSaved; };
		inline sf::Sprite& getSprite() const { return *sprite; };
		inline float getDepth() const override { return sprite->getPosition().y + 4; };
		inline void setEvent(std::function<void()> new_event) override { event_ = new_event; };
		inline void setHandler(std::function<void()> new_handler) override { handler_ = new_handler; };
		inline void event(sf::RenderWindow& window, sf::Event& event) override { if (event_) event_(); };
		void handler(sf::RenderWindow& window, sf::Event& event) override;
		void render(sf::RenderWindow& window, float delta, sf::View& game_camera, sf::Clock& clock) override;
	
	private:
		enum MouseState { Normal, Hovered, Pressed };
		MouseState mouseState = Normal;

		std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();
		sf::Sprite shadow;
		sf::Texture& idleTexture;
		sf::Texture& movementVertical;
		sf::Texture& movementHorizontal;
		sf::Texture& shadowTexture;

		bool isPressed = false;
		bool isDeltaSaved = false;
		float deltaSaved = 0.0f;
};