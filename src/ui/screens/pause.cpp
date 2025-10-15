#include "pause.hpp"

void Pause::setup() {
	initResources();
	initElements();
	initLayers();
	initParameters();
}

void Pause::initResources() {
	resourseManager.loadTexture("pause-panel", "../../../assets/textures/ui/pause/panel.png");
	resourseManager.loadTexture("pause-buttons", "../../../assets/textures/ui/pause/button.png");
	resourseManager.loadFont("nunito", "../../../assets/fonts/nunito.ttf");
}

void Pause::initElements() {
	uiManager.addElement("pause-background", uiManager.gui.createColorRect(sf::Color(0,0,0,100), {static_cast<float>(globals.getWindow().getSize().x),static_cast<float>(globals.getWindow().getSize().y)}));
	uiManager.addElement("pause-panel", uiManager.gui.createSprite(resourseManager.getTexture("pause-panel")));
	uiManager.addElement("pause-button-continue", uiManager.gui.createButton(resourseManager.getTexture("pause-buttons"), { 48,16 }));
	uiManager.addElement("pause-button-quit", uiManager.gui.createButton(resourseManager.getTexture("pause-buttons"), { 48,16 }));
	
	// labels
	uiManager.addElement("pause-button-continue-label", uiManager.gui.createLabel("Continue", resourseManager.getFont("nunito"), 24, sf::Color::White));
	uiManager.addElement("pause-button-quit-label", uiManager.gui.createLabel("Exit & Save", resourseManager.getFont("nunito"), 24, sf::Color::White));
}

void Pause::initLayers() {
	uiManager.getElement("pause-background")->setSortIndex(0);
	uiManager.getElement("pause-panel")->setSortIndex(1);
	uiManager.getElement("pause-button-continue")->setSortIndex(2);
	uiManager.getElement("pause-button-quit")->setSortIndex(2);

	uiManager.getElement("pause-button-continue-label")->setSortIndex(3);
	uiManager.getElement("pause-button-quit-label")->setSortIndex(3);
}

void Pause::initParameters() {
	initBackground();
	initPanel();
	initButtonContinue();
	initButtonExit();
	initLabels();
}

void Pause::initBackground() {
	if (uiManager.getElement("pause-background")) {
		uiManager.getElement("pause-background")->setVisible(false);
	}
}

void Pause::initPanel() {
	if (uiManager.getElement("pause-panel")) {
		auto panel = static_cast<Sprite*>(uiManager.getElement("pause-panel"));
		uiManager.getElement("pause-panel")->setGlobalPosition(UIElement::MiddleCenter, panel->getSprite());
		panel->setVisible(false);
		panel->setHandleEvent(
			[&]() {
				if (globals.getUIOpened()) return;

				static bool escWasPressed = false;
				bool escIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
				if (escIsPressed && !escWasPressed) {
					if (!globals.getGamePause()) {
						globals.setGamePause(true);
						uiManager.getElement("pause-background")->setVisible(true);
						uiManager.getElement("pause-panel")->setVisible(true);
						uiManager.getElement("pause-button-continue")->setVisible(true);
						uiManager.getElement("pause-button-quit")->setVisible(true);

						uiManager.getElement("pause-button-continue-label")->setVisible(true);
						uiManager.getElement("pause-button-quit-label")->setVisible(true);
					}
					else {
						globals.setGamePause(false);
						uiManager.getElement("pause-background")->setVisible(false);
						uiManager.getElement("pause-panel")->setVisible(false);
						uiManager.getElement("pause-button-continue")->setVisible(false);
						uiManager.getElement("pause-button-quit")->setVisible(false);

						uiManager.getElement("pause-button-continue-label")->setVisible(false);
						uiManager.getElement("pause-button-quit-label")->setVisible(false);
					}
				}; escWasPressed = escIsPressed;
			}
		);
	};
}

void Pause::initButtonContinue() {
	if (uiManager.getElement("pause-button-continue")) {
		auto button = static_cast<Button*>(uiManager.getElement("pause-button-continue"));
		auto panel = static_cast<Sprite*>(uiManager.getElement("pause-panel"));
		
		sf::Vector2f panelPosition = panel->getElementPosition();
		button->setRelativePosition(UIElement::TopCenter, panel->getSprite(), button->getSprite(), {0.f, 25});
		button->setVisible(false);
		button->setHandleEvent(
			[&]() {
				globals.setGamePause(false);
				uiManager.getElement("pause-background")->setVisible(!true);
				uiManager.getElement("pause-panel")->setVisible(false);
				uiManager.getElement("pause-button-continue")->setVisible(false);
				uiManager.getElement("pause-button-quit")->setVisible(false);

				uiManager.getElement("pause-button-continue-label")->setVisible(false);
				uiManager.getElement("pause-button-quit-label")->setVisible(false);
			}
		);
	}
}

void Pause::initButtonExit() {
	if (uiManager.getElement("pause-button-quit")) {
		auto button = static_cast<Button*>(uiManager.getElement("pause-button-quit"));
		auto panel = static_cast<Sprite*>(uiManager.getElement("pause-panel"));
		button->setRelativePosition(UIElement::TopCenter, panel->getSprite(), button->getSprite(), { 0.f, 100 });
		button->setVisible(false);
		button->setHandleEvent([&]() {globals.getWindow().close(); });
	}
}

void Pause::initLabels() {
	auto buttonContinue = static_cast<Button*>(uiManager.getElement("pause-button-continue"));
	auto buttonQuit = static_cast<Button*>(uiManager.getElement("pause-button-quit"));
	auto labelContinue = static_cast<Label*>(uiManager.getElement("pause-button-continue-label"));
	auto labelQuit = static_cast<Label*>(uiManager.getElement("pause-button-quit-label"));
	labelContinue->setRelativePositionText(UIElement::MiddleCenter, buttonContinue->getSprite(), labelContinue->getText(), { 0,-9 });
	labelQuit->setRelativePositionText(UIElement::MiddleCenter, buttonQuit->getSprite(), labelQuit->getText(), { 0,-9 });
	labelContinue->setVisible(false);
	labelQuit->setVisible(false);
}