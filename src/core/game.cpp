#include "game.hpp";

Game::Game() {
	window.setFramerateLimit(60);
	initilizeIcon();
	gameCamera = window.getDefaultView();
	UIView = window.getDefaultView();
}

void Game::run() {
	while (gameState.getWindowStatus()) {
		processEvent();
		render();
	}
}

void Game::processEvent() {
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gameState.setWindowStatus(false);
		}
	}
}

void Game::render() {
	window.clear(background);

	// Game
	window.setView(gameCamera);
	tilemap.render(window);
	world.render(window, event, delta, gameCamera, clock);

	// User Interface
	window.setView(UIView);
	UIManager.render(event, window);
	window.display();
}