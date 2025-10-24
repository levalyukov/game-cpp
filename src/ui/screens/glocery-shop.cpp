#include "glocery-shop.hpp"

void GloceryShop::setup() {
	initResources();
	initElements();
	initLayers();
	initParametes();
	initButtons();
	setVisible(false);
};

void GloceryShop::initResources() {
	resourceManager.loadTexture("glocery-panel", "../../../assets/textures/ui/glocery/menu.png");
	resourceManager.loadTexture("glocery-close-button", "../../../assets/textures/ui/glocery/close-button.png");
	resourceManager.loadTexture("glocery-button", "../../../assets/textures/ui/glocery/button.png");
};

void GloceryShop::initElements() {
	float windowX = static_cast<float>(Globals::instance().getWindow().getSize().x);
	float windowY = static_cast<float>(Globals::instance().getWindow().getSize().y);
	uiManager.addElement("glocery-background", uiManager.gui.createColorRect(sf::Color(0, 0, 0, 100), { windowX,windowY }));
	uiManager.addElement("glocery-panel", uiManager.gui.createSprite(resourceManager.getTexture("glocery-panel")));
	uiManager.addElement("glocery-close-button", uiManager.gui.createButton(resourceManager.getTexture("glocery-close-button"), { 16,16 }));
	uiManager.addElement("glocery-page-label", uiManager.gui.createLabel("0/0", resourceManager.getFont("nunito"), 22, sf::Color::White));
};

void GloceryShop::initLayers() {
	if (!uiManager.getElement("glocery-background")) return;
	auto background = static_cast<ColorRect*>(uiManager.getElement("glocery-background"));
	background->setSortIndex(SORT_INDEX_BACKGROUND);

	if (!uiManager.getElement("glocery-panel")) return;
	auto panel = static_cast<Sprite*>(uiManager.getElement("glocery-panel"));
	panel->setGlobalPosition(UIElement::MiddleCenter, panel->getSprite());
	panel->setSortIndex(SORT_INDEX_PANEL);

	if (!uiManager.getElement("glocery-close-button")) return;
	auto closeButton = static_cast<Button*>(uiManager.getElement("glocery-close-button"));
	sf::Sprite& closeButtonSprite = closeButton->getSprite();
	closeButton->setRelativePosition(UIElement::TopRight, panel->getSprite(), closeButtonSprite, { 80, -64 });
	closeButton->setSortIndex(SORT_INDEX_BUTTON);

	if (!uiManager.getElement("glocery-page-label")) return;
	auto pageLabel = static_cast<Label*>(uiManager.getElement("glocery-page-label"));
	pageLabel->setRelativePositionText(UIElement::BottomCenter, panel->getSprite(), pageLabel->getText(), {0, -24});
	pageLabel->setSortIndex(SORT_INDEX_TEXT);
};

void GloceryShop::initParametes() {
	if (!uiManager.getElement("glocery-close-button")) return;
	auto closeButton = static_cast<Button*>(uiManager.getElement("glocery-close-button"));
	closeButton->setHandleEvent([&]() {setVisible(false); });
};

void GloceryShop::initButtons() {
	if (gloceryShopManager.shop.size() == 0) return;

	if (page > 1) page = 1;
	maxPages = ceil(static_cast<double>(gloceryShopManager.shop.size()) / MAX_GLOCERY_SHOP_SLOTS);

	if (uiManager.getElement("glocery-page-label")) {
		auto pages = static_cast<Label*>(uiManager.getElement("glocery-page-label"));
		pages->setMessage(std::to_string(page) + "/" + std::to_string(static_cast<int>(maxPages)));
	};

	unsigned int index = 0;
	for (const auto& product : gloceryShopManager.shop) {
		std::string buttonName = "glocery-product-" + std::to_string(index);
		std::string buttonLabelName = "glocery-button-title-" + std::to_string(index);
		std::string buttonLabelPriceName = "glocery-button-title-" + std::to_string(index) + "-price";

		uiManager.removeElement(buttonName);
		uiManager.removeElement(buttonLabelName);
		uiManager.removeElement(buttonLabelPriceName);
		uiManager.addElement(buttonName, uiManager.gui.createButton(resourceManager.getTexture("glocery-button"), { 152,18 }));
		uiManager.addElement(buttonLabelName, uiManager.gui.createLabel(product.second.title, resourceManager.getFont("nunito"), 24, sf::Color::White));
		uiManager.addElement(buttonLabelPriceName, uiManager.gui.createLabel(std::to_string(product.second.price), resourceManager.getFont("nunito"), 24, sf::Color::White));

		auto panel = static_cast<Sprite*>(uiManager.getElement("glocery-panel"));
		auto buttonProduct = static_cast<Button*>(uiManager.getElement(buttonName));
		auto buttonLabel = static_cast<Label*>(uiManager.getElement(buttonLabelName));
		auto buttonLabelPrice = static_cast<Label*>(uiManager.getElement(buttonLabelPriceName));

		buttonProduct->setSortIndex(SORT_INDEX_BUTTON);
		buttonProduct->setVisible(false);
		buttonProduct->setRelativePosition(UIElement::TopLeft, panel->getSprite(), buttonProduct->getSprite(), { 16,16 + (static_cast<float>(index) * 80) });
		buttonProduct->setHandleEvent([&](){
			if (economyManager.getMoney() >= product.second.price) {
				warehouseManager.addItem(product.first, {product.second.title, product.second.icon, 1});
				economyManager.removeMoney(product.second.price);
				hud->update();
			} else {
				// todo: ... audioPlay() ...
			};
		});

		buttonLabel->setSortIndex(SORT_INDEX_TEXT);
		buttonLabel->setVisible(false);
		buttonLabel->setRelativePositionText(UIElement::TopLeft, buttonProduct->getSprite(), buttonLabel->getText(), {18, 18});
		
		buttonLabelPrice->setVisible(false);
		buttonLabelPrice->setSortIndex(SORT_INDEX_TEXT);
		buttonLabelPrice->setRelativePositionText(UIElement::TopRight, buttonProduct->getSprite(), buttonLabelPrice->getText(), { -18, 18 });
		
		index++;
	};
};

void GloceryShop::setVisible(bool new_state) {
	if (new_state != visible) {
		if (!uiManager.getElement("glocery-background")) return;
		if (!uiManager.getElement("glocery-panel")) return;
		if (!uiManager.getElement("glocery-close-button")) return;
		if (!uiManager.getElement("glocery-page-label")) return;

		visible = new_state;
		globals.setUIOpened(new_state);

		auto background = static_cast<ColorRect*>(uiManager.getElement("glocery-background"));
		auto panel = static_cast<Sprite*>(uiManager.getElement("glocery-panel"));
		auto closeButton = static_cast<Button*>(uiManager.getElement("glocery-close-button"));
		auto pageLabel = static_cast<Label*>(uiManager.getElement("glocery-page-label"));

		background->setVisible(visible);
		panel->setVisible(visible);
		closeButton->setVisible(visible);
		pageLabel->setVisible(visible);

		for (int i = 0; i < MAX_GLOCERY_SHOP_SLOTS; i++) {
			std::string buttonName = "glocery-product-" + std::to_string(i);
			std::string buttonLabelName = "glocery-button-title-" + std::to_string(i);
			std::string buttonLabelPriceName = "glocery-button-title-" + std::to_string(i) + "-price";

			if (uiManager.getElement(buttonName)) uiManager.getElement(buttonName)->setVisible(visible);
			if (uiManager.getElement(buttonLabelName)) uiManager.getElement(buttonLabelName)->setVisible(visible);
			if (uiManager.getElement(buttonLabelPriceName)) uiManager.getElement(buttonLabelPriceName)->setVisible(visible);
		};
	};
};