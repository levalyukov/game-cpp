#include "kitchen.hpp"

void KitchenMenu::setup() {
	initResources();
	initElements();
	initVisible();
	initLambdas();
}

void KitchenMenu::initResources() {
	resourceManager.loadTexture("kitchen-ui-panel", "../../../assets/textures/ui/kitchen/menu.png");
	resourceManager.loadTexture("kitchen-ui-buttons", "../../../assets/textures/ui/kitchen/buttons.png");
	resourceManager.loadTexture("kitchen-ui-close-button", "../../../assets/textures/ui/kitchen/close-button.png");
};

void KitchenMenu::initElements() {
	uiManager.addElement("kitchen-ui-background", uiManager.gui.createColorRect(sf::Color(0, 0, 0, 100), { static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y) }));
	uiManager.addElement("kitchen-ui-panel", uiManager.gui.createPanel(resourceManager.getTexture("kitchen-ui-panel"), { 0,0 }));
	uiManager.addElement("kitchen-ui-close-button", uiManager.gui.createButton(resourceManager.getTexture("kitchen-ui-close-button"), { 16,16 }));

	auto panel = static_cast<Panel*>(uiManager.getElement("kitchen-ui-panel"));
	auto close_button = static_cast<Button*>(uiManager.getElement("kitchen-ui-close-button"));
	sf::Sprite& close_button_sprite = close_button->getSprite();
	panel->setGlobalPosition(UIElement::MiddleCenter, panel->getSprite());
	close_button->setGlobalPosition(UIElement::TopRight, close_button_sprite);
	close_button_sprite.setPosition(close_button_sprite.getPosition().x + -240, close_button_sprite.getPosition().y + 128);

	float button_pos_y = 0.f;
	unsigned int new_id = 0;

	for (const auto& pair : cooking.recipes) {
		button_pos_y += 8;
		std::string buttonName = "kitchen-ui-recipe-button-" + std::to_string(new_id);
		std::string buttonRecipeName = pair.second.title;

		uiManager.addElement(buttonName, uiManager.gui.createButton(resourceManager.getTexture("kitchen-ui-buttons"), { 73,18 }, { 0,24 }));
		
		auto buttonRecipe = static_cast<Button*>(uiManager.getElement(buttonName));
		auto panel = static_cast<Panel*>(uiManager.getElement("kitchen-ui-panel"));
		sf::Sprite& buttonSprite = buttonRecipe->getSprite();

		buttonRecipe->setVisible(false);
		buttonRecipe->setRelativePosition(UIElement::TopLeft, panel->getSprite(), buttonRecipe->getSprite(), { 16,button_pos_y + (buttonSprite.getGlobalBounds().height * new_id + 1)+15 });
		buttonRecipe->setText(resourceManager.getFont("nunito"), pair.second.title, 22);
		buttonRecipe->setHandleEvent(
			[new_id, buttonRecipeName]() {
				std::cout << buttonRecipeName << std::endl;
			}
		);
		new_id++;
	}
};

void KitchenMenu::initVisible() {
	uiManager.getElement("kitchen-ui-background")->setVisible(false);
	uiManager.getElement("kitchen-ui-panel")->setVisible(false);
	uiManager.getElement("kitchen-ui-close-button")->setVisible(false);
}

void KitchenMenu::initLambdas() {
	uiManager.getElement("kitchen-ui-close-button")->setHandleEvent([]() {
			KitchenMenu& kitchen = KitchenMenu::instance();
			HUD& hud = HUD::instance();
			kitchen.setVisible(false);
			hud.setVisible(true);
		}
	);
}