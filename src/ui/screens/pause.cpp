#include "pause.hpp"

Pause::Pause() {
	initResources();
	initElements();
	createBackground();
	createButtonContinue();
	createButtonExit();
}

void Pause::initResources() {
	resourseManager.loadTexture("pause-panel", "../../../assets/textures/ui/panel.png");
	resourseManager.loadTexture("pause-button-continue", "../../../assets/textures/ui/button.png");
	resourseManager.loadTexture("pause-button-quit", "../../../assets/textures/ui/button.png");
	resourseManager.loadFont("nunito", "../../../assets/fonts/nunito.ttf");
}

void Pause::initElements() {Panel* panel = static_cast<Panel*>(uiManager.getElement("pause"));
	uiManager.addElement("pause", uiManager.gui.createPanel(resourseManager.getTexture("pause-panel"), { 250,260 }));
	uiManager.addElement("pause-button-continue", uiManager.gui.createButton(resourseManager.getTexture("pause-button-continue"), {0,0}));
	uiManager.addElement("pause-button-quit", uiManager.gui.createButton(resourseManager.getTexture("pause-button-quit"), {0,0}));
}

void Pause::createBackground() {
	if (uiManager.getElement("pause")) {
		Panel* panel = static_cast<Panel*>(uiManager.getElement("pause"));
		panel->setElementPosition(UIElement::MiddleCenter);
		panel->setVisible(false);
		panel->setHandleEvent(
			[]() {
				static bool escWasPressed = false;
				bool escIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

				if (escIsPressed && !escWasPressed) {
					Globals& globals = Globals::instance();
					UIManager& ui = UIManager::instance();
					if (!globals.getGamePause()) {
						globals.setGamePause(true);
						ui.getElement("pause")->setVisible(true);
						ui.getElement("pause-button-continue")->setVisible(true);
						ui.getElement("pause-button-quit")->setVisible(true);
					}
					else {
						globals.setGamePause(!true);
						ui.getElement("pause")->setVisible(!true);
						ui.getElement("pause-button-continue")->setVisible(!true);
						ui.getElement("pause-button-quit")->setVisible(!true);
					}
				}

				escWasPressed = escIsPressed;
			}
		);
	};
}

void Pause::createButtonContinue() {
	if (uiManager.getElement("pause-button-continue")) {
		Button* button = static_cast<Button*>(uiManager.getElement("pause-button-continue"));
		Panel* panel = static_cast<Panel*>(uiManager.getElement("pause"));
		
		button->setElementPosition(
			{
				panel->getElementPosition().x + (panel->getButtonSprite().getGlobalBounds().width - button->getButtonSprite().getGlobalBounds().width) / 2.0f,
				panel->getElementPosition().y + 25
			}
		);

		if (resourseManager.getFont("nunito")) {
			button->setText(
				resourseManager.getFont("nunito"),
				"Continue",
				24
			);
		}

		button->setVisible(false);
		button->setHandleEvent(
			[]() {
				Globals& globals = Globals::instance();
				UIManager& ui = UIManager::instance();
				globals.setGamePause(false);
				ui.getElement("pause")->setVisible(false);
				ui.getElement("pause-button-continue")->setVisible(false);
				ui.getElement("pause-button-quit")->setVisible(false);
			}
		);
	}
}

void Pause::createButtonExit() {
	if (uiManager.getElement("pause-button-quit")) {
		Button* button = static_cast<Button*>(uiManager.getElement("pause-button-quit"));
		Panel* panel = static_cast<Panel*>(uiManager.getElement("pause"));

		button->setElementPosition(
			{
				panel->getElementPosition().x + (panel->getButtonSprite().getGlobalBounds().width - button->getButtonSprite().getGlobalBounds().width) / 2.0f,
				panel->getElementPosition().y + 100
			}
		);

		if (resourseManager.getFont("nunito")) {
			button->setText(
				resourseManager.getFont("nunito"),
				"Exit the Game",
				24
			);
		}

		button->setVisible(false);
		button->setHandleEvent(
			[]() {
				Globals& globals = Globals::instance();
				globals.getWindow().close();
			}
		);
	}
}