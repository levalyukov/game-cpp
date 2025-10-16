#pragma once

#include <SFML/Graphics.hpp>

class Globals {
	public:
		Globals() {
			window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
			event = std::make_unique<sf::Event>();
			clock = std::make_unique<sf::Clock>();
		};
		
		~Globals() { window = nullptr; event = nullptr; clock = nullptr; };
		Globals(Globals& const) = delete;
		Globals& operator=(Globals& const) = delete;

		inline static Globals& instance() { static Globals gl; return gl; };
		inline sf::RenderWindow& getWindow() const { return *window; };
		inline sf::Event& getEvent() const { return *event; };
		inline sf::Clock& getClock() const { return *clock; };
		inline void setGamePause(bool new_state) { paused = new_state; };
		inline bool getGamePause() const { return paused; };
		inline void setUIOpened(bool new_state) { uiOpened = new_state; };
		inline bool getUIOpened() const { return uiOpened; };

	private:
		const size_t WINDOW_WIDTH = 1280;
		const size_t WINDOW_HEIGHT = 720;
		const std::string WINDOW_TITLE = "Delicious Soup";

		std::unique_ptr<sf::RenderWindow> window = nullptr;
		std::unique_ptr<sf::Event> event = nullptr;
		std::unique_ptr<sf::Clock> clock = nullptr;

		bool paused = false;
		bool uiOpened = false;
};