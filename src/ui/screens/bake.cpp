#include "bake.hpp"

void BakeMenu::setup() {
	initResources();
	initElements();
	initParameters();
	setVisible(false);
};

void BakeMenu::initResources() {
	resourceManager.loadTexture("bake-ui-panel", "../../../assets/textures/ui/bake/menu.png");
	resourceManager.loadTexture("bake-ui-buttons", "../../../assets/textures/ui/bake/buttons.png");
	resourceManager.loadTexture("bake-ui-close-button", "../../../assets/textures/ui/bake/close-button.png");
};

void BakeMenu::initElements() {
	uiManager.addElement("bake-ui-background", uiManager.gui.createColorRect(sf::Color(0, 0, 0, 100), { static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y) }));
	uiManager.addElement("bake-ui-panel", uiManager.gui.createSprite(resourceManager.getTexture("bake-ui-panel"), { 0,0 }));
	uiManager.addElement("bake-ui-close-button", uiManager.gui.createButton(resourceManager.getTexture("bake-ui-close-button"), { 16,16 }));
	uiManager.addElement("bake-ui-recipe-header", uiManager.gui.createLabel(L"Recipe header", resourceManager.getFont("nunito"), 26, sf::Color::White));
	uiManager.addElement("bake-ui-recipe-description", uiManager.gui.createLabel(L"Recipe Description", resourceManager.getFont("nunito"), 20, sf::Color::White));
	uiManager.addElement("bake-ui-recipe-conditions", uiManager.gui.createLabel(L"Recipe Conditions", resourceManager.getFont("nunito"), 20, sf::Color::White));
	uiManager.addElement("bake-ui-recipe-button-cooking", uiManager.gui.createButton(resourceManager.getTexture("bake-ui-buttons"), { 73,18 }));
	uiManager.addElement("bake-ui-recipe-button-cooking-label", uiManager.gui.createLabel(L"Cooking", resourceManager.getFont("nunito"), 24, sf::Color::White));
};

void BakeMenu::initParameters() {
	auto background = static_cast<ColorRect*>(uiManager.getElement("bake-ui-background"));
	auto panel = static_cast<Sprite*>(uiManager.getElement("bake-ui-panel"));
	background->setSortIndex(SORT_INDEX_BACKGROUND);
	panel->setGlobalPosition(UIElement::MiddleCenter, panel->getSprite());
	panel->setSortIndex(SORT_INDEX_PANEL);

	initCloseButton();
	initRecipeButtons();
	initRecipeInfo();
};

void BakeMenu::initCloseButton() {
	auto closeButton = static_cast<Button*>(uiManager.getElement("bake-ui-close-button"));
	sf::Sprite& closeButtonSprite = closeButton->getSprite();
	closeButton->setGlobalPosition(UIElement::TopRight, closeButtonSprite);
	closeButtonSprite.setPosition(closeButtonSprite.getPosition().x + -240, closeButtonSprite.getPosition().y + 128);
	closeButton->setHandleEvent([&]() { setVisible(false); currentRecipe.clear(); });
	closeButton->setSortIndex(SORT_INDEX_BUTTON);
};

void BakeMenu::initRecipeButtons() {
	float buttonPosY = 0.f;
	unsigned int id = 0;

	for (const auto& pair : cooking.availableRecipes) {
		buttonPosY += 8;
		std::string buttonName = "bake-ui-recipe-button-" + std::to_string(id);
		std::string buttonNameLabel = "bake-ui-recipe-button-" + std::to_string(id) + "-label";

		uiManager.addElement(buttonName, uiManager.gui.createButton(resourceManager.getTexture("bake-ui-buttons"), { 73,18 }, { 0,24 }));
		uiManager.addElement(buttonNameLabel, uiManager.gui.createLabel(pair.second.title, resourceManager.getFont("nunito"), 22, sf::Color::White));

		if (!uiManager.getElement("bake-ui-panel")) return;
		auto panel = static_cast<Sprite*>(uiManager.getElement("bake-ui-panel"));
		sf::Sprite& panelSprite = panel->getSprite();

		if (!uiManager.getElement(buttonName)) return;
		auto buttonRecipe = static_cast<Button*>(uiManager.getElement(buttonName));
		sf::Sprite& buttonSprite = buttonRecipe->getSprite();
		buttonRecipe->setSortIndex(SORT_INDEX_BUTTON);
		buttonRecipe->setVisible(false);
		buttonRecipe->setRelativePosition(UIElement::TopLeft, panelSprite, buttonSprite, { 16,buttonPosY + (buttonSprite.getGlobalBounds().height * id) + 8 });
		buttonRecipe->setHandleEvent([&]() { getRecipeInfo(pair.first); currentRecipe = pair.first; });
		
		if (!uiManager.getElement(buttonNameLabel)) return;
		auto labelRecipe = static_cast<Label*>(uiManager.getElement(buttonNameLabel));
		sf::Text& labelText = labelRecipe->getText();
		labelRecipe->setRelativePositionText(UIElement::TopLeft, buttonSprite, labelText, { 18.f,18.f });
		labelRecipe->setVisible(false);
		labelRecipe->setSortIndex(SORT_INDEX_TEXT);
		
		id++;
	}
};

void BakeMenu::initRecipeInfo() {
	auto panel = static_cast<Sprite*>(uiManager.getElement("bake-ui-panel"));
	auto cookingButton = static_cast<Button*>(uiManager.getElement("bake-ui-recipe-button-cooking"));
	auto cookingButtonLabel = static_cast<Label*>(uiManager.getElement("bake-ui-recipe-button-cooking-label"));

	/* Cooking button */
	cookingButton->setSortIndex(SORT_INDEX_BUTTON);
	cookingButton->setRelativePosition(UIElement::BottomRight, panel->getSprite(), cookingButton->getSprite(), { -16, -16 });
	cookingButton->setHandleEvent([&]() {
		setVisible(false);
		cooking.startCookProcess(currentRecipe);
		currentRecipe.clear();
	});

	cookingButtonLabel->setSortIndex(SORT_INDEX_TEXT);
	cookingButtonLabel->setPosition(
		{
			cookingButton->getSprite().getPosition().x - (cookingButtonLabel->getText().getGlobalBounds().width - cookingButton->getSprite().getGlobalBounds().width) / 2.f,
			cookingButton->getSprite().getPosition().y - (cookingButtonLabel->getText().getGlobalBounds().height - cookingButton->getSprite().getGlobalBounds().height) / 2.f - 8,
		}
	);

	/* Recipe header */
	auto labelHeader = static_cast<Label*>(uiManager.getElement("bake-ui-recipe-header"));
	auto labelDescription = static_cast<Label*>(uiManager.getElement("bake-ui-recipe-description"));
	labelHeader->setSortIndex(SORT_INDEX_TEXT);
	labelDescription->setSortIndex(SORT_INDEX_TEXT);
	labelDescription->setPosition(
		{
			cookingButton->getSprite().getPosition().x,
			panel->getSprite().getPosition().y + (labelHeader->getText().getGlobalBounds().height + labelDescription->getText().getGlobalBounds().height) + 48
		}
	);

	/* Recipe condition */
	auto labelConditions = static_cast<Label*>(uiManager.getElement("bake-ui-recipe-conditions"));
	labelConditions->setSortIndex(SORT_INDEX_TEXT);
	labelConditions->setPosition(
		{
			cookingButton->getSprite().getPosition().x,
			panel->getSprite().getPosition().y + (labelDescription->getText().getGlobalBounds().height + 32 + labelConditions->getText().getGlobalBounds().height) + 96
		}
	);
};

void BakeMenu::getRecipeInfo(std::string recipe_name) {
	auto panel = static_cast<Sprite*>(uiManager.getElement("bake-ui-panel"));
	auto cookingButton = static_cast<Button*>(uiManager.getElement("bake-ui-recipe-button-cooking"));
	auto labelHeader = static_cast<Label*>(uiManager.getElement("bake-ui-recipe-header"));
	auto labelDescription = static_cast<Label*>(uiManager.getElement("bake-ui-recipe-description"));
	auto labelConditions = static_cast<Label*>(uiManager.getElement("bake-ui-recipe-conditions"));
	auto buttonCooking = static_cast<Button*>(uiManager.getElement("bake-ui-recipe-button-cooking"));
	auto buttonCookingLabel = static_cast<Label*>(uiManager.getElement("bake-ui-recipe-button-cooking-label"));

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

void BakeMenu::setVisible(bool new_state) {
	visible = new_state;
	globals.setUIOpened(visible);
	uiManager.getElement("bake-ui-background")->setVisible(visible);
	uiManager.getElement("bake-ui-panel")->setVisible(visible);
	uiManager.getElement("bake-ui-close-button")->setVisible(visible);
	uiManager.getElement("bake-ui-recipe-header")->setVisible(visible);
	uiManager.getElement("bake-ui-recipe-description")->setVisible(visible);
	uiManager.getElement("bake-ui-recipe-conditions")->setVisible(visible);
	uiManager.getElement("bake-ui-recipe-button-cooking")->setVisible(visible);
	uiManager.getElement("bake-ui-recipe-button-cooking-label")->setVisible(visible);
	for (int y = 0; y < cooking.availableRecipes.size(); y++) {
		std::string buttonName = "bake-ui-recipe-button-" + std::to_string(y);
		std::string buttonNameLabel = "bake-ui-recipe-button-" + std::to_string(y) + "-label";
		if (uiManager.getElement(buttonName) && uiManager.getElement(buttonNameLabel)) {
			uiManager.getElement(buttonName)->setVisible(visible);
			uiManager.getElement(buttonNameLabel)->setVisible(visible);
		};
	};
};