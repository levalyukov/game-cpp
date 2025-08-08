#include "npc.hpp"

void NPC::handleEvent(sf::RenderWindow& window, sf::Event& event) {
	if (npc.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		direction = 0;
	}
}

void NPC::movement(float deltaTime) {
	if (!Globals::instance().getGamePause()) {
		switch (direction) {
			case 0:
				npc.setTexture(idle);
				npc.setTextureRect(sf::IntRect({ 16,0 }, { 16,16 }));
				break;

			case 1:
				npc.move(0, SPEED);
				anim.setAnimation(
					npc,
					movementHorizontal,
					UpSpriteCoords,
					4, 16, 16,
					animationTimer,
					AnimSpeed, deltaTime
				);
				break;

			case 2:
				npc.move(0, -SPEED);
				anim.setAnimation(
					npc,
					movementHorizontal,
					DownSpriteCoords,
					4, 16, 16,
					animationTimer,
					AnimSpeed, deltaTime
				);
				break;

			case 3:
				npc.move(-SPEED, 0);
				anim.setAnimation(
					npc,
					movementVertical,
					LeftSpriteCoords,
					4, 16, 16,
					animationTimer,
					AnimSpeed, deltaTime
				);
				break;

			case 4:
				npc.move(SPEED, 0);
				anim.setAnimation(
					npc,
					movementVertical,
					RightSpriteCoords,
					4, 16, 16,
					animationTimer,
					AnimSpeed, deltaTime
				);
				break;
		}
	}
}

void NPC::render(sf::RenderWindow& window, float deltaTime, sf::View& gameCamera, sf::Clock& clock) {
	window.draw(npc);
	window.draw(shadow);
	movement(deltaTime);
	shadow.setPosition(npc.getPosition());

	// Random direction
	if (!Globals::instance().getGamePause()) {
		if (clock.getElapsedTime().asSeconds() >= vectorTimeValue) {
			vectorTimeValue = utils.randi_range(1,5);
			direction = utils.randi_range(1,4);
			clock.restart();
		}
	} else {
		clock.restart();
	}
}