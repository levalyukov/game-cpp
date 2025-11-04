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
	auto balance = std::to_string(economyManager.getMoney());
	uiManager.addElement("hud-money", uiManager.gui.createLabel(std::wstring(balance.begin(), balance.end()), resourceManager.getFont("nunito"), 24, sf::Color::White));
	uiManager.addElement("hud-button-store", uiManager.gui.createButton(resourceManager.getTexture("hud-glorecy-button"), { 16,16 }));
};

void HUD::initLayers() {
	if (uiManager.getElement("hud-money")) {
		auto label = static_cast<Label*>(uiManager.getElement("hud-money"));
		label->setGlobalPositionText(UIElement::BottomLeft, label->getText(), { 8,-16 });
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
	buttonStore->setHandleEvent(
		[&]() {
			if (globals.getUIOpened()) return;
			gloceryShop.setVisible(true);
		}
	);
};

void HUD::update() {
	if (uiManager.getElement("hud-money")) {
		auto label = static_cast<Label*>(uiManager.getElement("hud-money"));
		auto balance = std::to_string(economyManager.getMoney());
		label->setMessage(std::wstring(balance.begin(), balance.end()));
		label->setGlobalPositionText(UIElement::BottomLeft, label->getText(), { 8,-16 });
	};
};