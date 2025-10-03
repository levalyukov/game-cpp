#include "player.hpp"

void Player::render(sf::RenderWindow& window, const float delta, sf::View& game_camera, sf::Clock& clock) {
	window.draw(shadow_sprite);
	window.draw(*player);
	movement(delta);
	shadow_sprite.setPosition(player->getPosition());
	game_camera.setCenter(player->getPosition());
};

void Player::movement(const float delta) {
	if (!stopped_flag) {
		bool movementUp = false;
		bool movementDown = false;
		bool movementLeft = false;
		bool movementRight = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			movementUp = true;
			direction = "up";
		}; if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			movementLeft = true;
			direction = "left";
		}; if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			movementDown = true;
			direction = "down";
		}; if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			movementRight = true;
			direction = "right";
		};

		std::string newDirection = direction;

		if (newDirection != currentDirection) {
			currentFrame = 0;
			animationTimer = 0.0f;
			currentDirection = newDirection;

			oldVectorUP = vectorUP;
			oldVectorDOWN = vectorDOWN;
			oldVectorLEFT = vectorLEFT;
			oldVectorRIGHT = vectorRIGHT;
		};

		float speed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? RUN_SPEED : WALK_SPEED;
		
		if (movementUp && !movementDown) player->move(0.0, -speed);
		if (movementDown && !movementUp) player->move(0.0, speed);
		if (movementLeft && !movementRight) player->move(-speed, 0.0);
		if (movementRight && !movementLeft) player->move(speed, 0.0);

		bool isMoving = (movementUp || movementDown || movementLeft || movementRight);

		if (isMoving) {
			float animationSpeed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? RUN_ANIM : WALK_ANIM;
			sf::Texture& target_texture = (currentDirection == "up" || currentDirection == "down") ? walkVertical : walkHorizontal;

			if (currentDirection == "up") {
				animations.setAnimation(
					*player,
					target_texture,
					oldVectorUP,
					4, { 16, 16 },
					animationTimer,
					animationSpeed,
					delta
				);
			}; if (currentDirection == "down") {
				animations.setAnimation(
					*player,
					target_texture,
					oldVectorDOWN,
					4, { 16, 16 },
					animationTimer,
					animationSpeed,
					delta
				);
			}; if (currentDirection == "left") {
				animations.setAnimation(
					*player,
					target_texture,
					oldVectorLEFT,
					4, { 16, 16 },
					animationTimer,
					animationSpeed,
					delta
				);
			}; if (currentDirection == "right") {
				animations.setAnimation(
					*player,
					target_texture,
					oldVectorRIGHT,
					4, { 16, 16 },
					animationTimer,
					animationSpeed,
					delta
				);
			};
		} else {
			player->setTexture(idle);
			if (currentDirection == "up") {
				player->setTextureRect(sf::IntRect(0, 0, 16, 16));
				oldVectorUP = vectorUP;
				animationTimer = 0.0;
			} if (currentDirection == "down") {
				player->setTextureRect(sf::IntRect(16, 0, 16, 16));
				oldVectorDOWN = vectorDOWN;
				animationTimer = 0.0;
			} if (currentDirection == "left") {
				player->setTextureRect(sf::IntRect(0, 16, 16, 16));
				oldVectorLEFT = vectorLEFT;
				animationTimer = 0.0;
			} if (currentDirection == "right") {
				player->setTextureRect(sf::IntRect(16, 16, 16, 16));
				oldVectorRIGHT = vectorRIGHT;
				animationTimer = 0.0;
			};
		};
	};
};