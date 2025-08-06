#pragma once

class GameState {
	public:
		static GameState& instance() {
			static GameState gs;
			return gs;
		};

		inline void setGamePause(bool state) { paused = state; };
		inline bool getGamePause() const { return paused; };
		inline void setWindowStatus(bool state) { windowOpen = state; };
		inline bool getWindowStatus() const { return windowOpen; };
		inline sf::RenderWindow& getGameWindow() const { return *window; };
		inline sf::Clock* getGameClock() const { return clock.get(); };

	private:
		bool paused = false;
		bool windowOpen = true;
		std::unique_ptr<sf::RenderWindow> window;
		std::unique_ptr<sf::Clock> clock;

		GameState() {
			window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 1280, 720 }), "WINDOW_TITLE");
			clock = std::make_unique<sf::Clock>();
		};
		~GameState() {};
		GameState(GameState& const) = delete;
		GameState& operator=(GameState& const) = delete;
};