#include "inventory.hpp"

void Inventory::setup() {
	initResources();
	initElements();
	initParameters();
	update();
};

void Inventory::initResources() {
	resourceManager.loadTexture("inventory-panel", "../../../assets/textures/ui/inventory/panel.png");
	resourceManager.loadTexture("inventory-slot", "../../../assets/textures/ui/inventory/slot.png");
};

void Inventory::initElements() {
	uiManager.addElement("inventory-panel", uiManager.gui.createPanel(resourceManager.getTexture("inventory-panel"), { 8.f,8.f }));
};

void Inventory::initParameters() {};

void Inventory::update() {
	if (inventoryManager.inventory.size() > 0) {
		if (inventoryManager.inventory.size() <= MAX_SLOTS) {
			for (int y = 0; y < inventoryManager.inventory.size(); y++) {
				if (!uiManager.getElement("inventory-slot-" + std::to_string(y))) {
					uiManager.addElement(
						"inventory-slot-" + std::to_string(y),
						uiManager.gui.createButton(
							resourceManager.getTexture("inventory-slot"),
							{ 16,16 }
						)
					);
					if (uiManager.getElement("inventory-slot-" + std::to_string(y))) {
						auto panel = static_cast<Panel*>(uiManager.getElement("inventory-panel"));
						auto slot = static_cast<Button*>(uiManager.getElement("inventory-slot-" + std::to_string(y)));
						slot->setSortIndex(1);
						slot->getSprite().setPosition(
							(panel->getSprite().getPosition().x + 8 + (y * 18 * 4)) + 12,
							panel->getSprite().getPosition().y + (panel->getSprite().getGlobalBounds().height - slot->getSprite().getGlobalBounds().height) / 2
						);
					};
				};
			};
		};

		for (auto& elements : uiManager.ui_elements) {
			if (elements.first.substr(0, 15) == "inventory-slot-") {
				const std::string id = elements.first.substr(15, 16);
				Button* slot = static_cast<Button*>(uiManager.getElement("inventory-slot-" + id));
				if (slot) {
					for (auto& item : inventoryManager.inventory) {
						slot->setIcon(item.second.icon_path);
						slot->setRelativePosition(
							UIElement::MiddleCenter,
							slot->getSprite(),
							slot->getIcon()
						);

						if (item.second.value > 1) {
							/*	
								String concatenation doesn't work for some reason:
								"inventory-slot-" + item.second.caption <- leads to an exception on Texture.cpp.
								I've tried many solutions, but nothing helps;
								Using item.second.caption is the only working solution, which is not the best option.
							*/

							std::transform(item.second.caption.begin(), item.second.caption.end(), item.second.caption.begin(), [](unsigned char c) {return std::tolower(c); });
							if (!uiManager.getElement(item.second.caption)) {
								uiManager.addElement(
									item.second.caption,
									uiManager.gui.createLabel(
										std::to_string(item.second.value),
										resourceManager.getFont("nunito"), 
										24, sf::Color::White
									)
								);

								auto item_label = static_cast<Label*>(uiManager.getElement(item.second.caption));
								item_label->setRelativePositionText(UIElement::BottomRight, slot->getSprite(), item_label->getText(), {-8, -16});
								item_label->setSortIndex(2);
							} else {
								std::transform(item.second.caption.begin(), item.second.caption.end(), item.second.caption.begin(), [](unsigned char c) {return std::tolower(c); });
								if (uiManager.getElement(item.second.caption)) {
									auto item_label = static_cast<Label*>(uiManager.getElement(item.second.caption));
									item_label->setMessage(std::to_string(item.second.value));
								};
							};
						};
					};
				};
			};
		};
	};
};