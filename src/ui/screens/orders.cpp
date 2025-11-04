#include "orders.hpp"

void OrdersDisplay::setup() {
	initResources();
	update();
};

void OrdersDisplay::initResources() {
	resourceManager.loadTexture("order", "../../../assets/textures/ui/orders/order.png");
	resourceManager.loadTexture("order-ready", "../../../assets/textures/ui/orders/order-ready.png");
	resourceManager.loadTexture("order-progress", "../../../assets/textures/ui/orders/progress-bar.png");
};

void OrdersDisplay::update() {
	for (int id = 0; id < MAX_ORDERS; id++) {
		std::string orderName = "order-" + std::to_string(id);
		std::string orderIcon = "order-" + std::to_string(id) + "-icon";
		std::string orderTitle = "order-title" + std::to_string(id);
		std::string orderProgress = "order-progress-bar-" + std::to_string(id);

		if (resourceManager.getTexture(orderIcon)) resourceManager.removeTexture(orderIcon);
		if (uiManager.getElement(orderName)) uiManager.removeElement(orderName);;
		if (uiManager.getElement(orderIcon)) uiManager.removeElement(orderIcon);;
		if (uiManager.getElement(orderTitle)) uiManager.removeElement(orderTitle);;
		if (uiManager.getElement(orderProgress)) uiManager.removeElement(orderProgress);;
	};

	int id = 0;
	int buttonX = 0;
	for (const auto& order : ordersManager.orders) {
		buttonX += 8;
		std::string orderName = "order-" + std::to_string(id);
		std::string orderIcon = "order-" + std::to_string(id) + "-icon";
		std::string orderTitle = "order-title" + std::to_string(id);
		std::string orderProgress = "order-progress-bar-" + std::to_string(id);
		auto& config = order.second;

		sf::Texture* orderTexture = (config.cookeed) ? resourceManager.getTexture("order-ready") : resourceManager.getTexture("order");
		if (!config.icon.empty()) if (!resourceManager.getTexture(orderIcon)) resourceManager.loadTexture(orderIcon, config.icon);
		if (orderTexture) uiManager.addElement(orderName, uiManager.gui.createSprite(orderTexture));
		if (resourceManager.getTexture(orderIcon)) uiManager.addElement(orderIcon, uiManager.gui.createSprite(resourceManager.getTexture(orderIcon)));
		if (!config.title.empty()) uiManager.addElement(orderTitle, uiManager.gui.createLabel(config.title, resourceManager.getFont("nunito"), 22, sf::Color::Black));
		if (!config.cookeed) uiManager.addElement(orderProgress, uiManager.gui.createProgressBar(resourceManager.getTexture("order-progress"), {32,3}));

		if (!uiManager.getElement(orderName)) return;
		auto orderBlock = static_cast<Sprite*>(uiManager.getElement(orderName));
		orderBlock->getSprite().setPosition({ buttonX + (orderBlock->getSprite().getGlobalBounds().width * static_cast<float>(id)),8 });
		orderBlock->setSortIndex(SORT_INDEX_ORDER);

		if (!uiManager.getElement(orderIcon)) return;
		auto orderIconSprite = static_cast<Sprite*>(uiManager.getElement(orderIcon));
		orderIconSprite->setSortIndex(SORT_INDEX_ICON);
		orderIconSprite->getSprite().setScale(2.5, 2.5);
		orderIconSprite->setRelativePosition(UIElement::TopCenter, orderBlock->getSprite(), orderIconSprite->getSprite());

		if (!uiManager.getElement(orderTitle)) return;
		auto orderTitleLabel = static_cast<Label*>(uiManager.getElement(orderTitle));
		orderTitleLabel->setSortIndex(SORT_INDEX_TITLE);
		orderTitleLabel->setRelativePositionText(UIElement::BottomCenter, orderBlock->getSprite(), orderTitleLabel->getText(), { 0,-32 });

		if (!uiManager.getElement(orderProgress)) return;
		if (!config.cookeed) {
			auto orderProgressBar = static_cast<ProgressBar*>(uiManager.getElement(orderProgress));
			orderProgressBar->setSortIndex(SORT_INDEX_PROGRESS_BAR);
			orderProgressBar->getSprite().setScale(3.5, 3.5);
			orderProgressBar->setRelativePosition(UIElement::BottomCenter, orderBlock->getSprite(), orderProgressBar->getSprite(), { 0, -8 });
			orderProgressBar->setValues(config.customer_wait, 0);
			orderProgressBar->setMode(true);
			orderProgressBar->setHandleEvent([&]() {ordersManager.removeOrder(order.first); this->update();});
		} else uiManager.removeElement(orderProgress);

		id++;
	};
};