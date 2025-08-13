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
		UIManager() {};
		~UIManager() {};
		UIManager(UIManager const&) = delete;
		UIManager& operator=(UIManager const&) = delete;
		static UIManager& instance() {
			static UIManager r;
			return r;
		};

		inline void addElement(std::string name_element, std::unique_ptr<UIElement> element) {
			std::transform(name_element.begin(), name_element.end(), name_element.begin(), [](unsigned char c) { return std::tolower(c); });
			auto result = ui_elements.emplace(name_element, std::move(element));
			if (result.second) {
				renderUI.push_back(result.first->second.get());
			}
		};

		inline UIElement* getElement(std::string name_element) {
			std::transform(name_element.begin(), name_element.end(), name_element.begin(), [](unsigned char c) { return std::tolower(c); });
			auto element = ui_elements.find(name_element);
			return (element != ui_elements.end()) ? element->second.get() : nullptr;
		};

		inline void removeElement(std::string name_element) {
			std::transform(name_element.begin(), name_element.end(), name_element.begin(), [](unsigned char c) { return std::tolower(c); });
			auto element = ui_elements.find(name_element);
			auto it = std::find(renderUI.begin(), renderUI.end(), element->second.get());
			if (element != ui_elements.end()) {
				renderUI.erase(it);
				ui_elements.erase(name_element);
			}
		};

		inline void render() {
			if (ui_elements.empty() && renderUI.empty()) return;

			std::sort(renderUI.begin(), renderUI.end(), [](UIElement* a, UIElement* b) {
				return a->getSortIndex() < b->getSortIndex();
			});

			for (auto& element : renderUI) {
				element->handleEvent(event, window);
				if (element->getVisible()) {
					element->render(window);
				}
			}
		};

		GUI gui;

	private:
		std::vector<UIElement*> renderUI;
		std::map<std::string, std::unique_ptr<UIElement>> ui_elements;

		Globals& global = Globals::instance();
		sf::RenderWindow& window = global.getWindow();
		sf::Event& event = global.getEvent();
};