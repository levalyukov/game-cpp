#include "kitchen.hpp"

KitchenMenu::KitchenMenu() {
	initResources();
	initElements();
	initElementsPosition();
	initVisible();
	initLambdas();
};

void KitchenMenu::initResources() {
	resourceManager.loadTexture("kitchen-ui-panel", "../../../assets/textures/ui/kitchen/menu.png");
	resourceManager.loadTexture("kitchen-ui-buttons", "../../../assets/textures/ui/kitchen/buttons.png");
	resourceManager.loadTexture("kitchen-ui-close-button", "../../../assets/textures/ui/kitchen/close-button.png");
};

void KitchenMenu::initElements() {
	uiManager.addElement("kitchen-ui-background", uiManager.gui.createColorRect(sf::Color(0, 0, 0, 100), { static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y) }));
	uiManager.addElement("kitchen-ui-panel", uiManager.gui.createPanel(resourceManager.getTexture("kitchen-ui-panel"), { 0,0 }));
	uiManager.addElement("kitchen-ui-close-button", uiManager.gui.createButton(resourceManager.getTexture("kitchen-ui-close-button"), { 16,16 }));
};

void KitchenMenu::initElementsPosition() {
	auto panel = static_cast<Panel*>(uiManager.getElement("kitchen-ui-panel"));
	auto close_button = static_cast<Button*>(uiManager.getElement("kitchen-ui-close-button"));
	panel->setGlobalPosition(UIElement::MiddleCenter, panel->getSprite());
	close_button->setGlobalPosition(UIElement::TopRight, close_button->getSprite());
	close_button->setMargins({-240, 128}, close_button->getSprite());
};

void KitchenMenu::initVisible() {
	uiManager.getElement("kitchen-ui-background")->setVisible(false);
	uiManager.getElement("kitchen-ui-panel")->setVisible(false);
	uiManager.getElement("kitchen-ui-close-button")->setVisible(false);
}

void KitchenMenu::initLambdas() {
	/* Close button */
	uiManager.getElement("kitchen-ui-close-button")->setHandleEvent([]() {
			KitchenMenu& kitchen = KitchenMenu::instance();
			HUD& hud = HUD::instance();
			kitchen.setVisible(false);
			hud.setVisible(true);
		}
	);
}