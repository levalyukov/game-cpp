#include "hud.hpp"

void HUD::setup() {
	initResources();
	initElements();
	initLayers();
	initParameters();
};

void HUD::initResources() {
	resourceManager.loadTexture("hud-glorecy-button", "../../../assets/textures/ui/hud/glorecy-button.png");
};

void HUD::initElements() {
	uiManager.addElement("hud-money", uiManager.gui.createLabel(std::to_string(economyManager.getMoney()), resourceManager.getFont("nunito"), 24, sf::Color::White));
	uiManager.addElement("hud-button-store", uiManager.gui.createButton(resourceManager.getTexture("hud-glorecy-button"), { 16,16 }));
};

void HUD::initLayers() {
	if (uiManager.getElement("hud-money")) {
		auto label = static_cast<Label*>(uiManager.getElement("hud-money"));
		label->setGlobalPositionText(UIElement::TopRight, label->getText(), { -8,8 });
		label->setSortIndex(SORT_INDEX_MONEY);
	};

	if (uiManager.getElement("hud-button-store")) {
		auto buttonStore = static_cast<Button*>(uiManager.getElement("hud-button-store"));
		buttonStore->setGlobalPosition(UIElement::BottomRight, buttonStore->getSprite(), { -8, -8 });
		buttonStore->setSortIndex(SORT_INDEX_GLOCERY);
	};
};

void HUD::initParameters() {
	if (!uiManager.getElement("hud-button-store")) return;
	auto buttonStore = static_cast<Button*>(uiManager.getElement("hud-button-store"));
	buttonStore->setHandleEvent([&]() {gloceryShop.setVisible(true); });
};

void HUD::update() {
	if (uiManager.getElement("hud-money")) {
		auto label = static_cast<Label*>(uiManager.getElement("hud-money"));
		label->setMessage(std::to_string(economyManager.getMoney()));
		label->setGlobalPositionText(UIElement::TopRight, label->getText(), { -8,8 });
	};
};