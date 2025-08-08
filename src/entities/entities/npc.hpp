#pragma once

#include "../entity.hpp"
#include "../../core/animations/animations.hpp"
#include "../../core/utils.hpp"
#include "../../core/globals.hpp"

#include <iostream>
#include <SFML/System.hpp>

class NPC : public Entity {
	public:
		NPC(
			sf::Texture* idle_texture,
			sf::Texture* movement_vertical,
			sf::Texture* movement_horizontal,
			sf::Texture* shdw
		) : idle(std::move(*idle_texture)),
			movementVertical(std::move(*movement_vertical)),
			movementHorizontal(std::move(*movement_horizontal)),
			npcShadow(std::move(*shdw)) {
			npc.setTexture(idle);
			npc.setTextureRect(sf::IntRect({16,0}, {16,16}));
			shadow.setTexture(npcShadow);
			npc.setScale({ 4,4 });
			shadow.setScale({ 4,4 });
			npc.setPosition({52*16,52*16});
			direction = 1;
		}

		void movement(float deltaTime);
		void handleEvent(sf::RenderWindow& window, sf::Event& event) override;
		void render(sf::RenderWindow& window, float deltaTime, sf::View& gameCamera, sf::Clock& clock) override;
	
	private:
		sf::Sprite npc;
		sf::Sprite shadow;
		sf::Texture idle;
		sf::Texture movementVertical;
		sf::Texture movementHorizontal;
		sf::Texture npcShadow;

		sf::Vector2i coords = { 8,0 };
		sf::Vector2f position = { 0,0 };

		sf::Vector2i UpSpriteCoords = { 0,0 };
		sf::Vector2i DownSpriteCoords = { 0,16 };
		sf::Vector2i LeftSpriteCoords = { 0,0 };
		sf::Vector2i RightSpriteCoords = { 0,16 };

		float animationTimer = 0.0f;
		const float SPEED = 1.75f;
		const float AnimSpeed = 0.035f;
		float timer = 0.0;
		int direction = 0; // Stub
		int vectorTimeValue = 0;

		Animations anim;
		Utils utils;
};