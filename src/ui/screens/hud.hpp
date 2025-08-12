#pragma once

#include "../../core/resources/resources.hpp"
#include "../ui-manager.hpp"

class HUD {
	public:
		HUD() {
			resource.loadFont("nunito", "../../../assets/fonts/nunito.ttf");

			ui.addElement(
				"Label",
				ui.gui.createLabel(
					"Delicious Soup",
					resource.getFont("nunito"),
					24, sf::Color::White,
					UIElement::BottomCenter,
					{ 25,25 }
				)
			);
		};

	protected:
		ResourceManager& resource = ResourceManager::instance();
		UIManager& ui = UIManager::instance();
};