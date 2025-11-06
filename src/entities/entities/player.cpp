#include "player.hpp"

void Player::render(sf::RenderWindow& window, const float delta, sf::View& camera, sf::Clock& clock) {
	if (shadowSprite) window.draw(*shadowSprite);
	if (player) window.draw(*player);
	if (itemSprite) { 
		window.draw(*itemSprite); 
		itemSprite->setPosition(player->getPosition().x + 12, player->getPosition().y - 20);
	}; movement(delta);
	shadowSprite->setPosition(player->getPosition()); 
	camera.setCenter(player->getPosition());
};

void Player::movement(const float delta) {
	printf("X: %.2f | Y: %.2f\n", player->getPosition().x / 64, player->getPosition().y/64);
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

			bool hasItem = selectedItem > 0;
			bool isVertical = (currentDirection == "up" || currentDirection == "down");

			auto& animationSet = hasItem ?
				(isVertical ? movementItemVertical : movementItemHorizontal) :
				(isVertical ? movementVertical : movementHorizontal);

			sf::Vector2i offset;
			if (currentDirection == "up") offset = { 0,16 };
			else if (currentDirection == "down") offset = { 0,0 };
			else if (currentDirection == "left") offset = { 16,0 };
			else offset = { 0,16 };

			anim.update(*player, animationSet, offset, { 16,16 }, animationSpeed, 3, delta);
		} else {
			if (selectedItem == 0) player->setTexture(idle);
			else player->setTexture(itemIdle);

			sf::Vector2i offset;
			if (currentDirection == "up") { offset = { 0,0 }; oldVectorUP = vectorUP; }
			else if (currentDirection == "down") { offset = { 16,0 }; oldVectorDOWN = vectorDOWN; }
			else if (currentDirection == "left") { offset = { 0,16 }; oldVectorLEFT = vectorLEFT; }
			else { offset = { 16,16 }; oldVectorRIGHT = vectorRIGHT; }

			player->setTextureRect(sf::IntRect(offset, {16,16}));
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