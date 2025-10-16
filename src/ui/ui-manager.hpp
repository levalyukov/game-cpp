#pragma once

#include "gui.hpp"
#include "elements/ui-element.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

class UIManager {
	public:
		GUI gui;
		std::vector<UIElement*> renderUI;
		std::map<std::string, std::shared_ptr<UIElement>> ui_elements;

		inline void addElement(const std::string name_element, std::unique_ptr<UIElement> element) {
			std::string lower_name = name_element;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto result = ui_elements.emplace(lower_name, std::move(element));
			if (result.second) renderUI.emplace_back(result.first->second.get());
		};

		inline UIElement* getElement(const std::string name_element) {
			std::string lower_name = name_element;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto element = ui_elements.find(lower_name);
			return (element != ui_elements.end()) ? element->second.get() : nullptr;
		};

		inline void removeElement(const std::string name_element) {
			std::string lower_name = name_element;
			std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), [](unsigned char c) { return std::tolower(c); });
			auto element = ui_elements.find(lower_name);
			if (element != ui_elements.end()) {
				auto it = std::find(renderUI.begin(), renderUI.end(), element->second.get());
				if (it != renderUI.end()) renderUI.erase(it);
				ui_elements.erase(lower_name);
			};
		};

		inline void render(sf::RenderWindow& window, sf::Event& event, const float delta) {
			if (ui_elements.empty() && renderUI.empty()) return;

			std::sort(renderUI.begin(), renderUI.end(), [](UIElement* a, UIElement* b) {
				return a->getSortIndex() < b->getSortIndex();
			});

			for (auto& element : renderUI) {
				element->handleEvent(event, window, delta);
				if (element->getVisible()) element->render(window);
			};
		};
};