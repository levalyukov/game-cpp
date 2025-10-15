#include "kitchen.hpp"

void KitchenMenu::setup() {
	initResources();
	initElements();
	initParameters();
	setVisible(false);
};

void KitchenMenu::initResources() {
	resourceManager.loadTexture("kitchen-ui-panel", "../../../assets/textures/ui/kitchen/menu.png");
	resourceManager.loadTexture("kitchen-ui-buttons", "../../../assets/textures/ui/kitchen/buttons.png");
	resourceManager.loadTexture("kitchen-ui-close-button", "../../../assets/textures/ui/kitchen/close-button.png");
};

void KitchenMenu::initElements() {
	uiManager.addElement("kitchen-ui-background", uiManager.gui.createColorRect(sf::Color(0, 0, 0, 100), { static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y) }));
	uiManager.addElement("kitchen-ui-panel", uiManager.gui.createSprite(resourceManager.getTexture("kitchen-ui-panel"), { 0,0 }));
	uiManager.addElement("kitchen-ui-close-button", uiManager.gui.createButton(resourceManager.getTexture("kitchen-ui-close-button"), { 16,16 }));
	uiManager.addElement("kitchen-ui-recipe-header", uiManager.gui.createLabel("Recipe header", resourceManager.getFont("nunito"), 26, sf::Color::White));
	uiManager.addElement("kitchen-ui-recipe-description", uiManager.gui.createLabel("Recipe Description", resourceManager.getFont("nunito"), 20, sf::Color::White));
	uiManager.addElement("kitchen-ui-recipe-conditions", uiManager.gui.createLabel("Recipe Conditions", resourceManager.getFont("nunito"), 20, sf::Color::White));
	uiManager.addElement("kitchen-ui-recipe-button-cooking", uiManager.gui.createButton(resourceManager.getTexture("kitchen-ui-buttons"), { 73,18 }));
	uiManager.addElement("kitchen-ui-recipe-button-cooking-label", uiManager.gui.createLabel("Cooking", resourceManager.getFont("nunito"), 24, sf::Color::White));
};

void KitchenMenu::initParameters() {
	auto background = static_cast<ColorRect*>(uiManager.getElement("kitchen-ui-background"));
	auto panel = static_cast<Sprite*>(uiManager.getElement("kitchen-ui-panel"));
	background->setSortIndex(SORT_INDEX_BACKGROUND);
	panel->setGlobalPosition(UIElement::MiddleCenter, panel->getSprite());
	panel->setSortIndex(SORT_INDEX_PANEL);

	initCloseButton();
	initRecipeButtons();
	initRecipeInfo();
};

void KitchenMenu::initCloseButton() {
	auto closeButton = static_cast<Button*>(uiManager.getElement("kitchen-ui-close-button"));
	sf::Sprite& closeButtonSprite = closeButton->getSprite();
	closeButton->setGlobalPosition(UIElement::TopRight, closeButtonSprite);
	closeButtonSprite.setPosition(closeButtonSprite.getPosition().x + -240, closeButtonSprite.getPosition().y + 128);
	uiManager.getElement("kitchen-ui-close-button")->setHandleEvent([&]() { setVisible(false); currentRecipe.clear(); });
};

void KitchenMenu::initRecipeButtons() {
	float buttonPosY = 0.f;
	unsigned int id = 0;

	for (const auto& pair : cooking.availableRecipes) {
		buttonPosY += 8;
		std::string buttonName = "kitchen-ui-recipe-button-" + std::to_string(id);
		std::string buttonNameLabel = "kitchen-ui-recipe-button-" + std::to_string(id) + "-label";

		uiManager.addElement(buttonName, uiManager.gui.createButton(resourceManager.getTexture("kitchen-ui-buttons"), { 73,18 }, { 0,24 }));
		uiManager.addElement(buttonNameLabel, uiManager.gui.createLabel(pair.second.title, resourceManager.getFont("nunito"), 22, sf::Color::White));

		auto panel = static_cast<Sprite*>(uiManager.getElement("kitchen-ui-panel"));
		auto buttonRecipe = static_cast<Button*>(uiManager.getElement(buttonName));
		auto labelRecipe = static_cast<Label*>(uiManager.getElement(buttonNameLabel));

		sf::Sprite& buttonSprite = buttonRecipe->getSprite();
		sf::Sprite& panelSprite = panel->getSprite();
		sf::Text& labelText = labelRecipe->getText();

		buttonRecipe->setSortIndex(SORT_INDEX_BUTTON);
		buttonRecipe->setVisible(false);
		buttonRecipe->setRelativePosition(UIElement::TopLeft, panelSprite, buttonSprite, { 16,buttonPosY + (buttonSprite.getGlobalBounds().height * id) + 8 });
		buttonRecipe->setHandleEvent([&]() { getRecipeInfo(pair.first); currentRecipe = pair.first; });
		
		labelRecipe->setRelativePositionText(UIElement::TopLeft, buttonSprite, labelText, { 18.f,18.f });
		labelRecipe->setVisible(false);
		labelRecipe->setSortIndex(SORT_INDEX_TEXT);
		
		id++;
	}
};

void KitchenMenu::initRecipeInfo() {
	auto panel = static_cast<Sprite*>(uiManager.getElement("kitchen-ui-panel"));
	auto cookingButton = static_cast<Button*>(uiManager.getElement("kitchen-ui-recipe-button-cooking"));
	auto cookingButtonLabel = static_cast<Label*>(uiManager.getElement("kitchen-ui-recipe-button-cooking-label"));

	/* Cooking button */
	cookingButton->setSortIndex(SORT_INDEX_BUTTON);
	cookingButton->setRelativePosition(UIElement::BottomRight, panel->getSprite(), cookingButton->getSprite(), { -16, -16 });
	cookingButton->setHandleEvent(
		[&]() {
			setVisible(false);
			cooking.startCookProcess(currentRecipe);
			currentRecipe.clear();
		}
	);

	cookingButtonLabel->setSortIndex(SORT_INDEX_TEXT);
	cookingButtonLabel->setPosition(
		{
			cookingButton->getSprite().getPosition().x - (cookingButtonLabel->getText().getGlobalBounds().width - cookingButton->getSprite().getGlobalBounds().width) / 2.f,
			cookingButton->getSprite().getPosition().y - (cookingButtonLabel->getText().getGlobalBounds().height - cookingButton->getSprite().getGlobalBounds().height) / 2.f - 8,
		}
	);

	/* Recipe header */
	auto labelHeader = static_cast<Label*>(uiManager.getElement("kitchen-ui-recipe-header"));
	auto labelDescription = static_cast<Label*>(uiManager.getElement("kitchen-ui-recipe-description"));
	labelHeader->setSortIndex(SORT_INDEX_TEXT);
	labelDescription->setSortIndex(SORT_INDEX_TEXT);
	labelDescription->setPosition(
		{
			cookingButton->getSprite().getPosition().x,
			panel->getSprite().getPosition().y + (labelHeader->getText().getGlobalBounds().height + labelDescription->getText().getGlobalBounds().height) + 48
		}
	);

	/* Recipe condition */
	auto labelConditions = static_cast<Label*>(uiManager.getElement("kitchen-ui-recipe-conditions"));
	labelConditions->setSortIndex(SORT_INDEX_TEXT);
	labelConditions->setPosition(
		{
			cookingButton->getSprite().getPosition().x,
			panel->getSprite().getPosition().y + (labelDescription->getText().getGlobalBounds().height + 32 + labelConditions->getText().getGlobalBounds().height) + 96
		}
	);
};

void KitchenMenu::getRecipeInfo(std::string recipe_name) {
	auto panel = static_cast<Sprite*>(uiManager.getElement("kitchen-ui-panel"));
	auto cookingButton = static_cast<Button*>(uiManager.getElement("kitchen-ui-recipe-button-cooking"));
	auto labelHeader = static_cast<Label*>(uiManager.getElement("kitchen-ui-recipe-header"));
	auto labelDescription = static_cast<Label*>(uiManager.getElement("kitchen-ui-recipe-description"));
	auto labelConditions = static_cast<Label*>(uiManager.getElement("kitchen-ui-recipe-conditions"));
	auto buttonCooking = static_cast<Button*>(uiManager.getElement("kitchen-ui-recipe-button-cooking"));
	auto buttonCookingLabel = static_cast<Label*>(uiManager.getElement("kitchen-ui-recipe-button-cooking-label"));

	if (!labelHeader->getVisible() && !labelDescription->getVisible() && !labelConditions->getVisible() && !buttonCooking->getVisible()) {
		labelHeader->setVisible(true);
		labelDescription->setVisible(true);
		labelConditions->setVisible(true);
		buttonCooking->setVisible(true);
		buttonCookingLabel->setVisible(true);
	};

	labelHeader->setMessage(cooking.availableRecipes[recipe_name].title);
	labelDescription->setMessage(cooking.availableRecipes[recipe_name].description);
	labelHeader->setPosition(
		{
			cookingButton->getSprite().getPosition().x - (labelHeader->getText().getGlobalBounds().width - cookingButton->getSprite().getGlobalBounds().width) / 2.f,
			panel->getSprite().getPosition().y + 32
		}
	);
};

void KitchenMenu::setVisible(bool new_state) {
	visible = new_state;
	globals.setUIOpened(visible);
	uiManager.getElement("kitchen-ui-background")->setVisible(visible);
	uiManager.getElement("kitchen-ui-panel")->setVisible(visible);
	uiManager.getElement("kitchen-ui-close-button")->setVisible(visible);
	uiManager.getElement("kitchen-ui-recipe-header")->setVisible(visible);
	uiManager.getElement("kitchen-ui-recipe-description")->setVisible(visible);
	uiManager.getElement("kitchen-ui-recipe-conditions")->setVisible(visible);
	uiManager.getElement("kitchen-ui-recipe-button-cooking")->setVisible(visible);
	uiManager.getElement("kitchen-ui-recipe-button-cooking-label")->setVisible(visible);
	for (int y = 0; y < cooking.availableRecipes.size(); y++) {
		std::string buttonName = "kitchen-ui-recipe-button-" + std::to_string(y);
		std::string buttonNameLabel = "kitchen-ui-recipe-button-" + std::to_string(y) + "-label";
		if (uiManager.getElement(buttonName) && uiManager.getElement(buttonNameLabel)) {
			uiManager.getElement(buttonName)->setVisible(visible);
			uiManager.getElement(buttonNameLabel)->setVisible(visible);
		};
	};
};