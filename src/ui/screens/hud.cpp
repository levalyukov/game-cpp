#include "hud.hpp"

void HUD::setup() {
	initResources();
	initElements();
	initLayers();
}

void HUD::initResources() {};

void HUD::initElements() {
	uiManager.addElement(
		"hud-money",
		uiManager.gui.createLabel(
			std::to_string(economyManager.getMoney()),
			resourceManager.getFont("nunito"),
			24, sf::Color::White
		)
	);

	if (uiManager.getElement("hud-money")) {
		auto label = static_cast<Label*>(uiManager.getElement("hud-money"));
		label->setGlobalPositionText(UIElement::TopRight, label->getText(), { -10,5 });
	};
};

void HUD::initLayers() {};

void HUD::update() {
	if (uiManager.getElement("hud-money")) {
		auto label = static_cast<Label*>(uiManager.getElement("hud-money"));
		label->setMessage(std::to_string(economyManager.getMoney()));
	};
};