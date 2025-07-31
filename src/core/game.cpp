#include "game.hpp";

Game::Game() {
	sf::err().setstate(std::ios_base::failbit);

	window.create(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEGHT }), WINDOW_TITLE);
	window.setFramerateLimit(60);
	initilizeIcon();

	gameView = window.getDefaultView();
	UIView = window.getDefaultView();

	resourceManager.loadTexture("character-idle", "../../../assets/textures/entity/player/character_idle.png");
	resourceManager.loadTexture("character-walk-horizontal", "../../../assets/textures/entity/player/character_walk_horizontal.png");
	resourceManager.loadTexture("character-walk-vertical", "../../../assets/textures/entity/player/character_walk_vertical.png");
	resourceManager.loadTexture("character-shadow", "../../../assets/textures/entity/player/character_shadow.png");

	entityManager.addEntity(
		"player",
		std::make_unique<Player>(
			resourceManager.getTexture("character-idle"),
			resourceManager.getTexture("character-walk-horizontal"),
			resourceManager.getTexture("character-walk-vertical"),
			resourceManager.getTexture("character-shadow")
		)
	);
}

void Game::run() {
	while (window.isOpen()) {
		processEvent();
		render();
	}
}

void Game::processEvent() {
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

void Game::render() {
	window.clear(background);

	// Game
	window.setView(gameView);
	tilemap.render(window);
	entityManager.render(window, deltaTime, gameView);

	// User Interface
	window.setView(UIView);
	UIManager.render(event, window);
	window.display();
}