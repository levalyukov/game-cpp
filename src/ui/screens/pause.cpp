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

void Pause::initElements() {
	uiManager.addElement("pause", uiManager.gui.createPanel(resourseManager.getTexture("pause-panel"), { 250,260 }));
	uiManager.addElement("pause-button-continue", uiManager.gui.createButton(resourseManager.getTexture("pause-button-continue"), { 250,250 }));
	uiManager.addElement("pause-button-quit", uiManager.gui.createButton(resourseManager.getTexture("pause-button-quit"), { 250,375 }));
}

void Pause::createBackground() {
	if (uiManager.getElement("pause")) {
		uiManager.getElement("pause")->setVisible(false);
		uiManager.getElement("pause")->setHandleEvent(
			[]() {
				static bool escWasPressed = false;
				bool escIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

				if (escIsPressed && !escWasPressed) {
					GameState& gameStates = GameState::instance();
					UIManager& ui = UIManager::instance();
					if (!gameStates.getGamePause()) {
						gameStates.setGamePause(true);
						ui.getElement("pause")->setVisible(true);
						ui.getElement("pause-button-continue")->setVisible(true);
						ui.getElement("pause-button-quit")->setVisible(true);
					}
					else {
						gameStates.setGamePause(!true);
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
		Button* continueButton = static_cast<Button*>(uiManager.getElement("pause-button-continue"));

		if (resourseManager.getFont("nunito")) {
			continueButton->setText(
				resourseManager.getFont("nunito"),
				"Continue",
				24
			);
		}

		continueButton->setVisible(false);
		continueButton->setHandleEvent(
			[]() {
				GameState& gameStates = GameState::instance();
				UIManager& ui = UIManager::instance();
				gameStates.setGamePause(false);
				ui.getElement("pause")->setVisible(false);
				ui.getElement("pause-button-continue")->setVisible(false);
				ui.getElement("pause-button-quit")->setVisible(false);
			}
		);
	}
}

void Pause::createButtonExit() {
	if (uiManager.getElement("pause-button-quit")) {
		Button* quitButton = static_cast<Button*>(uiManager.getElement("pause-button-quit"));

		if (resourseManager.getFont("nunito")) {
			quitButton->setText(
				resourseManager.getFont("nunito"),
				"Exit the Game",
				24
			);
		}

		quitButton->setVisible(false);
		quitButton->setHandleEvent(
			[]() {
				GameState& game = GameState::instance();
				game.setWindowStatus(false);
			}
		);
	}
}