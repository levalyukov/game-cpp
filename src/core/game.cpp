#include "game.hpp";

Game::Game() {
	sf::err().setstate(std::ios_base::failbit);

	window.create(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEGHT }), WINDOW_TITLE);
	window.setFramerateLimit(60);
	initilizeIcon();

	gameCamera = window.getDefaultView();
	UIView = window.getDefaultView();
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
	window.setView(gameCamera);
	tilemap.render(window);
	world.render(window, event, deltaTime, gameCamera, clock);

	// User Interface
	window.setView(UIView);
	UIManager.render(event, window);
	window.display();
}