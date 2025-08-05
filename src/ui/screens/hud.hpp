#pragma once

#include "../../core/resources/resources.hpp"
#include "../core/ui.hpp"

class HUD {
	public:
		HUD() {
			resource.loadFont("nunito", "../../../assets/fonts/nunito.ttf");
			//resource.loadFont("arial", "../../../assets/fonts/arial.ttf");

			ui.addElement(
				"Label",
				ui.gui.createLabel(
					"Delicious Soup",
					resource.getFont("nunito"),
					24, sf::Color::White,
					{ 25,25 }, UIElement::BottomCenter
				)
			);
		};

	private:
		ResourceManager& resource = ResourceManager::Instance();
		UIManager& ui = UIManager::Instance();
};