#include "player.hpp"

void Player::render(sf::RenderWindow& window, float deltaTime, sf::View& gameView, sf::Clock& clock) {
	window.draw(shadow_sprite);
	window.draw(player);
	movement(deltaTime);
	shadow_sprite.setPosition(player.getPosition());
	gameView.setCenter(player.getPosition());
}

void Player::movement(float deltaTime) {
	bool movementUp = false;
	bool movementDown = false;
	bool movementLeft = false;
	bool movementRight = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movementUp = true;
		direction = "up";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movementLeft = true;
		direction = "left";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movementDown = true;
		direction = "down";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movementRight = true;
		direction = "right";
	}

	std::string newDirection = direction;

	if (newDirection != currentDirection) {
		currentFrame = 0;
		animationTimer = 0.0f;
		currentDirection = newDirection;

		oldVectorUP	= vectorUP;
		oldVectorDOWN = vectorDOWN;
		oldVectorLEFT = vectorLEFT;
		oldVectorRIGHT = vectorRIGHT;
	}

	// Movement
	float speed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? RUN_SPEED : WALK_SPEED;
	if (movementUp && !movementDown) player.move(0.0, -speed);
	if (movementDown && !movementUp) player.move(0.0, speed);
	if (movementLeft && !movementRight) player.move(-speed, 0.0);
	if (movementRight && !movementLeft) player.move(speed, 0.0);

	bool isMoving = (movementUp || movementDown || movementLeft || movementRight);

	// Animation play
	if (isMoving) {
		float animationSpeed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? RUN_ANIM : WALK_ANIM;
		sf::Texture& target_texture = (currentDirection == "up" || currentDirection == "down") ? walkVertical : walkHorizontal;

		if (currentDirection == "up") {
			animations.setAnimation(
				player,
				target_texture,
				oldVectorUP,
				4, 16, 16,
				animationTimer,
				animationSpeed,
				deltaTime
			);
		}

		if (currentDirection == "down") {
			animations.setAnimation(
				player,
				target_texture,
				oldVectorDOWN,
				4, 16, 16,
				animationTimer,
				animationSpeed,
				deltaTime
			);
		}

		if (currentDirection == "left") {
			animations.setAnimation(
				player,
				target_texture,
				oldVectorLEFT,
				4, 16, 16,
				animationTimer,
				animationSpeed,
				deltaTime
			);
		}

		if (currentDirection == "right") {
			animations.setAnimation(
				player,
				target_texture,
				oldVectorRIGHT,
				4, 16, 16,
				animationTimer,
				animationSpeed,
				deltaTime
			);
		}
	}
	else {
		player.setTexture(idle);
		if (currentDirection == "up") {
			player.setTextureRect(sf::IntRect(0, 0, 16, 16));
			oldVectorUP = vectorUP;
		}
		if (currentDirection == "down") {
			player.setTextureRect(sf::IntRect(16, 0, 16, 16));
			oldVectorDOWN = vectorDOWN;
		}
		if (currentDirection == "left") {
			player.setTextureRect(sf::IntRect(0, 16, 16, 16));
			oldVectorLEFT = vectorLEFT;
		}
		if (currentDirection == "right") {
			player.setTextureRect(sf::IntRect(16, 16, 16, 16));
			oldVectorRIGHT = vectorRIGHT;
		}
	}
}