#pragma once
#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <map>
#include <vector>
#include <string.h>
#include <algorithm>
#include "elements/element.hpp"

class UIManager {
	public:
    inline bool addElement(const std::string& name, std::unique_ptr<UIElement> element) {
      if (!element) return false;

      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
      [](unsigned char c) {return std::tolower(c); });
      
      if (!getElement(copy)) {
        elementsSort.emplace_back(std::move(element.get()));
        elements.emplace(copy, std::move(element));
        return true;
      }; return false;
    };

    inline UIElement* getElement(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
      [](unsigned char c) {return std::tolower(c); });

      auto element = elements.find(copy);
      return (element != elements.end()) ? element->second.get() : nullptr;
    };

    inline bool removeElement(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
      [](unsigned char c) {return std::tolower(c); });

      auto element = elements.find(copy);
      if (element == elements.end()) return false;

      auto it = std::find(elementsSort.begin(), 
      elementsSort.end(), element->second.get());
      if (it == elementsSort.end()) return false;

      elementsSort.erase(it);
      elements.erase(copy);
      return true;
    };

    inline void update(sf::RenderWindow& window, sf::Event& event) {
      if (elements.empty()) return;

      std::sort(elementsSort.begin(), elementsSort.end(), 
      [](UIElement* a, UIElement* b) { return a->getDepth() < b->getDepth(); });

      for (const auto& element : elements) {
        if (element.second) element.second->update(window, event);
      };
    };
  private:
    std::vector<UIElement*> elementsSort;
    std::map<std::string, std::unique_ptr<UIElement>> elements;
};

#endif 