#pragma once

#include "../../core/resources/resources.hpp"
#include "../core/ui.hpp"

#include <iostream>

class Pause {
	public:
		inline void pauseMenu() {
			resourseManager.loadTexture("panel", "../../../assets/textures/ui/panel.png");

			uiManager.addElement(
				"Pause",
				uiManager.gui.createPanel(
					resourseManager.getTexture("panel"),
					{250,260}
				)
			);

			if (uiManager.getElement("Pause")) uiManager.getElement("Pause")->setHandleEvent([] {std::cout << "hello c++!" << std::endl; });
		}

	private:
		ResourceManager& resourseManager = ResourceManager::Instance();
		UIManager& uiManager = UIManager::Instance();
};