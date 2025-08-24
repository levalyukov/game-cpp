#include "pause.hpp"

void Pause::setup() {
	initResources();
	initElements();
	initLayers();
	createBackground();
	createPanel();
	createButtonContinue();
	createButtonExit();
}

void Pause::initResources() {
	resourseManager.loadTexture("pause-panel", "../../../assets/textures/ui/pause/panel.png");
	resourseManager.loadTexture("pause-buttons", "../../../assets/textures/ui/pause/button.png");
	resourseManager.loadFont("nunito", "../../../assets/fonts/nunito.ttf");
}

void Pause::initElements() {
	uiManager.addElement("pause-background", uiManager.gui.createColorRect(sf::Color(0,0,0,100), {static_cast<float>(globals.getWindow().getSize().x),static_cast<float>(globals.getWindow().getSize().y)}));
	uiManager.addElement("pause-panel", uiManager.gui.createPanel(resourseManager.getTexture("pause-panel")));
	uiManager.addElement("pause-button-continue", uiManager.gui.createButton(resourseManager.getTexture("pause-buttons"), { 48,16 }));
	uiManager.addElement("pause-button-quit", uiManager.gui.createButton(resourseManager.getTexture("pause-buttons"), { 48,16 }));
}

void Pause::initLayers() {
	uiManager.getElement("pause-background")->setSortIndex(0);
	uiManager.getElement("pause-panel")->setSortIndex(1);
	uiManager.getElement("pause-button-continue")->setSortIndex(2);
	uiManager.getElement("pause-button-quit")->setSortIndex(2);
}

void Pause::createBackground() {
	if (uiManager.getElement("pause-background")) {
		uiManager.getElement("pause-background")->setVisible(false);
	}
}

void Pause::createPanel() {
	if (uiManager.getElement("pause-panel")) {
		Panel* panel = static_cast<Panel*>(uiManager.getElement("pause-panel"));
		uiManager.getElement("pause-panel")->setGlobalPosition(UIElement::MiddleCenter, panel->getSprite());
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
						ui.getElement("pause-background")->setVisible(true);
						ui.getElement("pause-panel")->setVisible(true);
						ui.getElement("pause-button-continue")->setVisible(true);
						ui.getElement("pause-button-quit")->setVisible(true);
					}
					else {
						globals.setGamePause(!true);
						ui.getElement("pause-background")->setVisible(!true);
						ui.getElement("pause-panel")->setVisible(!true);
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
		Panel* panel = static_cast<Panel*>(uiManager.getElement("pause-panel"));
		
		button->setElementPosition(
			{
				panel->getElementPosition().x + (panel->getSprite().getGlobalBounds().width - button->getSprite().getGlobalBounds().width) / 2.0f,
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
				ui.getElement("pause-background")->setVisible(!true);
				ui.getElement("pause-panel")->setVisible(false);
				ui.getElement("pause-button-continue")->setVisible(false);
				ui.getElement("pause-button-quit")->setVisible(false);
			}
		);
	}
}

void Pause::createButtonExit() {
	if (uiManager.getElement("pause-button-quit")) {
		Button* button = static_cast<Button*>(uiManager.getElement("pause-button-quit"));
		Panel* panel = static_cast<Panel*>(uiManager.getElement("pause-panel"));

		button->setElementPosition(
			{
				panel->getElementPosition().x + (panel->getSprite().getGlobalBounds().width - button->getSprite().getGlobalBounds().width) / 2.0f,
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