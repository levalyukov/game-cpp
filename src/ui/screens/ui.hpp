#pragma once

#include "pause.hpp"
#include "hud.hpp"
#include "orders.hpp"
#include "kitchen.hpp"

class UI {
	/* for init only */
	private:
		Pause pause;
		HUD hud;
		OrdersDisplay orders;
		KitchenMenu kitchen_ui;
};