#include "npc.hpp"

void NPC::movement(float deltaTime) {
	switch (direction) {
		case 1: 
			npc.move(0, SPEED);
			anim.setAnimation(
				npc,
				movementHorizontal,
				UpCoords,
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
				DownCoords,
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
				LeftCoords,
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
				RightCoords,
				4, 16, 16,
				animationTimer,
				AnimSpeed, deltaTime
			);
			break;
	}
}

void NPC::render(sf::RenderWindow& window, float deltaTime, sf::View& gameCamera, sf::Clock& clock) {
	window.draw(npc);
	window.draw(shadow);
	movement(deltaTime);
	shadow.setPosition(npc.getPosition());

	// Random direction
	if (clock.getElapsedTime().asSeconds() >= vectorTimeValue) {
		vectorTimeValue = utils.randi_range(1,5);
		direction = utils.randi_range(1,4);
		clock.restart();
	}
}