#include "npc.hpp"

void NPC::handleEvent(sf::RenderWindow& window, sf::Event& event) {
	if (npc.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		bool isHovered = npc.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		switch (event.type) {
			case sf::Event::MouseMoved:
				if (!isPressed) m_state = isHovered ? Hovered : Normal;
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left && isHovered) {
					m_state = Pressed;
					isPressed = true;
				}; break;

			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left && isPressed) {
					if (isHovered && m_state == Pressed) { if (handler) handler(); };
					m_state = isHovered ? Hovered : Normal;
					isPressed = false;
				}; break;
		};
	};
};

void NPC::movement(float deltaTime) {
	if (!stopped_flag) {
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
					4, { 16, 16 },
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
					4, { 16, 16 },
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
					4, { 16, 16 },
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
					4, { 16, 16 },
					animationTimer,
					AnimSpeed, deltaTime
				);
				break;
		};
	};
};

void NPC::render(sf::RenderWindow& window, float delta_time, sf::View& game_camera, sf::Clock& clock) {
	window.draw(npc);
	window.draw(shadow);
	movement(delta_time);
	shadow.setPosition(npc.getPosition());

	// Random direction, change this in the future!
	if (!Globals::instance().getGamePause()) {
		if (clock.getElapsedTime().asSeconds() >= vectorTimeValue) {
			vectorTimeValue = utils.randi_range(1, 5);
			direction = utils.randi_range(0, 4);
			clock.restart();
		}
	} else {
		clock.restart();
	};
};