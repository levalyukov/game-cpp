/*
	sdasdas
	asda
*/

#pragma once

class GameState {
	public:
		static GameState& instance() {
			static GameState gs;
			return gs;
		};

		inline void setGamePause(bool state) { paused = state; };
		inline bool getGamePause() const { return paused; };
		inline void setWindowStatus(bool state) { window = state; };
		inline bool getWindowStatus() const { return window; };

	private:
		bool paused;
		bool window = true;

		GameState() {};
		~GameState() {};
		GameState(GameState& const) = delete;
		GameState& operator=(GameState& const) = delete;
};