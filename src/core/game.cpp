#include "game.hpp"

void Game::run() {
	while (window.isOpen()) {
		processEvent();
		render();
	};
};

void Game::processEvent() {
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
	};
};

void Game::render() {
	window.clear(sf::Color::Black);
	window.setView(main_camera);
	tilemap->render();
	world->render(delta, main_camera);
	window.setView(ui_camera);
	uiManager->render(window, event);
	window.display();
};