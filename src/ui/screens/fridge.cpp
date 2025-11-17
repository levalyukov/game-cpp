#include "fridge.hpp"

void Fridge::setup() {
	initResources();
	initElements();
	initLayers();
	initParameters();
	setVisible(false);
};

void Fridge::initResources() {
	resourceManager.loadTexture("fridge-panel", "../../../assets/textures/ui/fridge/panel.png");
	resourceManager.loadTexture("fridge-close-button", "../../../assets/textures/ui/fridge/close-button.png");
	resourceManager.loadTexture("fridge-button", "../../../assets/textures/ui/fridge/button.png");
	resourceManager.loadTexture("fridge-button-disabled", "../../../assets/textures/ui/fridge/button-disabled.png");
};

void Fridge::initElements() {
	sf::Vector2u windowSize = Globals::instance().getWindow().getSize();
	float windowX = static_cast<float>(windowSize.x);
	float windowY = static_cast<float>(windowSize.y);
	uiManager.addElement("fridge-background", uiManager.gui.createColorRect(sf::Color(0, 0, 0, 100), { windowX,windowY }));
	uiManager.addElement("fridge-panel", uiManager.gui.createSprite(resourceManager.getTexture("fridge-panel")));
	uiManager.addElement("fridge-close-button", uiManager.gui.createButton(resourceManager.getTexture("fridge-close-button"), { 16,16 }));
};

void Fridge::initLayers() {
	if (!uiManager.getElement("fridge-background")) return;
	if (!uiManager.getElement("fridge-panel")) return;
	if (!uiManager.getElement("fridge-close-button")) return;
	
	auto background = static_cast<ColorRect*>(uiManager.getElement("fridge-background"));
	auto panel = static_cast<Sprite*>(uiManager.getElement("fridge-panel"));
	auto closeButton = static_cast<Button*>(uiManager.getElement("fridge-close-button"));

	background->setSortIndex(SORT_INDEX_BACKGROUND);
	panel->setSortIndex(SORT_INDEX_PANEL);
	closeButton->setSortIndex(SORT_INDEX_BUTTON);
};

void Fridge::initParameters() {
	if (!uiManager.getElement("fridge-panel")) return;
	auto panel = static_cast<Sprite*>(uiManager.getElement("fridge-panel"));
	panel->setGlobalPosition(UIElement::MiddleCenter, panel->getSprite());
	
	if (!uiManager.getElement("fridge-close-button")) return;
	auto closeButton = static_cast<Button*>(uiManager.getElement("fridge-close-button"));
	closeButton->setRelativePosition(UIElement::TopRight, panel->getSprite(), closeButton->getSprite(), {80, -64});
	closeButton->setHandleEvent([&]() {setVisible(false); });
};

void Fridge::update() {
	
};

void Fridge::setVisible(const bool new_state) {
	visible = new_state;
	globals.setUIOpened(visible);

	if (!uiManager.getElement("fridge-background")) return;
	if (!uiManager.getElement("fridge-panel")) return;
	if (!uiManager.getElement("fridge-close-button")) return;

	uiManager.getElement("fridge-background")->setVisible(visible);
	uiManager.getElement("fridge-panel")->setVisible(visible);
	uiManager.getElement("fridge-close-button")->setVisible(visible);
};