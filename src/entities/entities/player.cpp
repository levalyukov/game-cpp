#include "player.hpp"

void Player::render(sf::RenderWindow& window, const float delta, sf::View& camera, sf::Clock& clock) {
	window.draw(shadowSprite);
	window.draw(*player);
	if (itemSprite) { 
		window.draw(*itemSprite); 
		itemSprite->setPosition(player->getPosition().x + 12, player->getPosition().y - 20);
	};
	movement(delta);
	shadowSprite.setPosition(player->getPosition());
	camera.setCenter(player->getPosition());
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
		if (selectedItem > 0) speed = WALK_SPEED / 1.5;
		
		if (movementUp && !movementDown) player->move(0.0, -speed);
		if (movementDown && !movementUp) player->move(0.0, speed);
		if (movementLeft && !movementRight) player->move(-speed, 0.0);
		if (movementRight && !movementLeft) player->move(speed, 0.0);

		bool isMoving = (movementUp || movementDown || movementLeft || movementRight);
	
		if (isMoving) {
			float animationSpeed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? RUN_ANIM : WALK_ANIM;
			if (selectedItem > 0) animationSpeed = WALK_ANIM * 1.5;
			sf::Texture& targetTexture = (currentDirection == "up" || currentDirection == "down") ? movementVertical : movementHorizontal;
			if (selectedItem > 0) targetTexture = (currentDirection == "up" || currentDirection == "down") ? movementItemVertical : movementItemHorizontal;
			
			if (currentDirection == "up") anim.update(*player, targetTexture, { 0,16 }, { 16,16 }, animationSpeed, 3, delta);
			if (currentDirection == "down") anim.update(*player, targetTexture, { 0,0 }, { 16,16 }, animationSpeed, 3, delta); 
			if (currentDirection == "left") anim.update(*player, targetTexture, { 16,0 }, { 16,16 }, animationSpeed, 3, delta);
			if (currentDirection == "right") anim.update(*player, targetTexture, { 0,16 }, { 16,16 }, animationSpeed, 3, delta);
		} else {
			if (selectedItem == 0) player->setTexture(idle);
			else player->setTexture(itemIdle);
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

void Player::setSelectedItem(const uint8_t new_item, Items& items) {
	selectedItem = new_item;
	if (selectedItem == 0) {
		if (itemSprite) itemSprite = nullptr;
	} else {
		if (!itemSprite) {
			itemSprite = std::make_unique<sf::Sprite>();
			if (itemSprite) {
				itemTexture = std::make_unique<sf::Texture>();
				if (!itemTexture->loadFromFile(items.getItemInfo(selectedItem)->icon)) itemSprite = nullptr;
				itemSprite->setTexture(*itemTexture);
				itemSprite->setScale(1.25, 1.25);
			};
		};
	};
};