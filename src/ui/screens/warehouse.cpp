#include "warehouse.hpp"

void Warehouse::setup() {
	initResources();
	initElements();
	initLayers();
	initParameters();
	setVisible(false);
};

void Warehouse::initResources() {
	resourceManager.loadTexture("warehouse-panel", "../../../assets/textures/ui/warehouse/panel.png");
	resourceManager.loadTexture("warehouse-close-button", "../../../assets/textures/ui/warehouse/close-button.png");
	resourceManager.loadTexture("warehouse-button", "../../../assets/textures/ui/warehouse/button.png");
	resourceManager.loadTexture("warehouse-button-disabled", "../../../assets/textures/ui/warehouse/button-disabled.png");
};

void Warehouse::initElements() {
	sf::Vector2u windowSize = Globals::instance().getWindow().getSize();
	float windowX = static_cast<float>(windowSize.x);
	float windowY = static_cast<float>(windowSize.y);
	uiManager.addElement("warehouse-background", uiManager.gui.createColorRect(sf::Color(0, 0, 0, 100), { windowX,windowY }));
	uiManager.addElement("warehouse-panel", uiManager.gui.createPanel(resourceManager.getTexture("warehouse-panel")));
	uiManager.addElement("warehouse-close-button", uiManager.gui.createButton(resourceManager.getTexture("warehouse-close-button"), { 16,16 }));
};

void Warehouse::initLayers() {
	if (!uiManager.getElement("warehouse-background")) return;
	if (!uiManager.getElement("warehouse-panel")) return;
	if (!uiManager.getElement("warehouse-close-button")) return;
	
	auto background = static_cast<ColorRect*>(uiManager.getElement("warehouse-background"));
	auto panel = static_cast<Panel*>(uiManager.getElement("warehouse-panel"));
	auto closeButton = static_cast<Button*>(uiManager.getElement("warehouse-close-button"));

	background->setSortIndex(SORT_INDEX_BACKGROUND);
	panel->setSortIndex(SORT_INDEX_PANEL);
	closeButton->setSortIndex(SORT_INDEX_BUTTON);
};

void Warehouse::initParameters() {
	if (!uiManager.getElement("warehouse-panel")) return;
	if (!uiManager.getElement("warehouse-close-button")) return;

	auto panel = static_cast<Panel*>(uiManager.getElement("warehouse-panel"));
	auto closeButton = static_cast<Button*>(uiManager.getElement("warehouse-close-button"));

	panel->setGlobalPosition(UIElement::MiddleCenter, panel->getSprite());
	closeButton->setRelativePosition(UIElement::TopRight, panel->getSprite(), closeButton->getSprite(), {80, -64});
	closeButton->setHandleEvent([&]() {setVisible(false); });
};

void Warehouse::update() {
	
};

void Warehouse::setVisible(const bool new_state) {
	visible = new_state;
	globals.setUIOpened(visible);

	if (!uiManager.getElement("warehouse-background")) return;
	if (!uiManager.getElement("warehouse-panel")) return;
	if (!uiManager.getElement("warehouse-close-button")) return;

	uiManager.getElement("warehouse-background")->setVisible(visible);
	uiManager.getElement("warehouse-panel")->setVisible(visible);
	uiManager.getElement("warehouse-close-button")->setVisible(visible);
};