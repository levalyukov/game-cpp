#pragma once

#include "pause.hpp"
#include "hud.hpp"
#include "orders.hpp"
#include "kitchen.hpp"

class UI {
	/* for init only */
	public: 
		UI() { allSetup(); };
		~UI() {};
		UI(UI& const) = delete;
		UI& operator=(UI& const) = delete;

		inline void allSetup() {
			pause.setup();
			hud.setup();
			kitchen_ui.setup();
			orders.setup();
		};

	private:
		Pause pause;
		HUD hud;
		OrdersDisplay orders;
		KitchenMenu kitchen_ui;
};