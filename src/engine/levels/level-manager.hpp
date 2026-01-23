#pragma once
#ifndef ENGINE_LEVEL_MANAGER_H
#define ENGINE_LEVEL_MANAGER_H

#include <map>
#include <iostream>
#include <algorithm>
#include "level.hpp"
#include <SFML/Graphics.hpp>

class LevelManager {
  public:
    inline bool addLevel(const std::string& name, std::unique_ptr<Level> level) {
      if (!level) return false;

      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
      [](unsigned char c) {return std::tolower(c); });

      if (!getLevel(copy)) {
        levels.emplace(copy, std::move(level));
        return true;
      }; return false;
    };

    inline bool setLevel(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
      [](unsigned char c) {return std::tolower(c); });

      auto lvl = getLevel(copy);
      if (lvl) {
        pointer = lvl;
        return true;
      }; return false;
    };

    inline Level* getLevel(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(), 
      [](unsigned char c) {return std::tolower(c); });

      auto lvl = levels.find(copy);
      return (lvl != levels.end()) ? lvl->second.get() : nullptr;
    };

    inline bool removeLevel(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
      [](unsigned char c) {return std::tolower(c); });

      auto lvl = levels.find(copy);
      if (lvl != levels.end()) {
        if (pointer) {
          if (pointer == lvl->second.get()) pointer = nullptr;
        }; levels.erase(lvl);
        return true;
      }; return false;
    };

    inline Level* getPointer(void) const { return pointer; };

    inline void update(sf::RenderWindow& window, sf::Event& event) {
      if (levels.empty()) return;
      if (pointer) pointer->update(window, event);
    };

  private:
    std::map<std::string, std::unique_ptr<Level>> levels;
    Level* pointer = nullptr;
};

#endif