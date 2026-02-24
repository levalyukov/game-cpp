#pragma once

#include <map>
#include <memory>
#include <algorithm>
#include <functional>
#include "element.hpp"
#if defined(DEBUG)
#include <logger.h>
#endif

class UIContainer : public UIElement {
  public:
    inline bool addElement(const std::string& name, 
      std::shared_ptr<UIElement>&& element) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      if (!getElement(copy)) {
        container.emplace(copy, std::move(element));
        return true;
      }; return false;
    };

    inline UIElement* getElement(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      auto element = container.find(copy);
      return (element != container.end()) ? element->second.get() : nullptr;
    };

    inline bool removeElement(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      auto element = container.find(copy);
      if (element != container.end()) {
        container.erase(element);
        return true;
      }; return false;
    };

    inline int16_t getDepth(void) const override { return depth; };
    inline bool getVisible(void) const override { return visible; };
    inline void setDepth(const int16_t new_depth) override { depth = new_depth; };
    inline void setFunction(const std::function<void()> func) { if (func) lambda = func; };

    inline void setVisible(const bool& new_state) override {
      if (container.empty()) {
        #if defined(DEBUG)
        LOGI("UI container is empty.");
        #endif
        return;
      };

      for (const auto& items : container) {
        if (items.second) {
          items.second->setVisible(new_state);
          #if defined(DEBUG) 
          LOGI("Changed visible (%i) for: %s", new_state, items.first);
          #endif
        };
      };
    };

    inline void update(sf::RenderWindow& window, sf::Event& event) override {
      if (container.empty()) return;

      for (const auto& items : container) {
        if (items.second) {
          if (items.second->getVisible())
            items.second->update(window, event);
        };
      };

      if (lambda) lambda();
    };

  private:
    int16_t depth = 0;
    bool visible = true;
    std::function<void()> lambda;
    std::map<std::string, std::shared_ptr<UIElement>> container;
};