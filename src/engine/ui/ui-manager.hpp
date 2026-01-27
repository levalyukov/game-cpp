#pragma once
#ifndef ENGINE_UI_MANAGER_H
#define ENGINE_UI_MANAGER_H

#include <map>
#include <vector>
#include <string.h>
#include <algorithm>
#include "elements/element.hpp"

class UIManager {
	public:

    /* -- UI Elements -- */
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

    inline UIElement* getElement(const std::string& name) const {
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
    /* ----------------- */

    /* -- Fonts -- */
    inline bool addFont(const std::string& name, const std::string& path_to_font) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      if (!getFont(copy)) {
        std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
        if (!font->loadFromFile(path_to_font)) return false;
        fonts.emplace(copy, std::move(font));
        return true;
      }; return false;
    };

    inline sf::Font* getFont(const std::string& name) const {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      auto font = fonts.find(copy);
      return (font != fonts.end()) ? font->second.get() : nullptr;
    };

    inline bool removeFont(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      auto font = fonts.find(copy);
      if (font != fonts.end()) {
        fonts.erase(font);
        return true;
      }; return false;
    };

    /* ----------- */

    /* -- Textures -- */
    inline bool addTexture(const std::string& name, const std::string& path_to_texture) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      if (!getTexture(copy)) {
        std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(path_to_texture)) return false;
        textures.emplace(copy, std::move(texture));
        return true;
      }; return false;
    };

    inline sf::Texture* getTexture(const std::string& name) const {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      auto texture = textures.find(copy);
      return texture != textures.end() ? texture->second.get() : nullptr;
    };

    inline bool removeTexture(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      auto texture = textures.find(copy);
      if (texture != textures.end()) {
        textures.erase(copy);
        return true;
      }; return false;
    };

  private:
    std::vector<UIElement*> elementsSort;
    std::map<std::string, std::unique_ptr<UIElement>> elements;
    std::map<std::string, std::unique_ptr<sf::Font>> fonts;
    std::map<std::string, std::unique_ptr<sf::Texture>> textures;
};

#endif 