#include "game.hpp"

void Game::run() {
	while (window.isOpen()) {
		processEvent();
		render();
	}
}

void Game::processEvent() {
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
	}
}

void Game::render() {
	window.clear(sf::Color::Black);
	window.setView(main_camera);
	tilemap.render(window);
	world.render(window, event, delta, main_camera, clock);
	window.setView(ui_camera);
	UIManager.render(event, window);
	window.display();
}