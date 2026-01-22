#pragma once
#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <map>
#include <algorithm>
#include "levels/level.hpp"
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
        poiner = lvl;
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
        levels.erase(lvl);
        return true;
      }; return false;
    };

    inline void update(sf::RenderWindow& window, sf::Event& event) {
      if (levels.empty()) return;
      if (poiner) poiner->update(window, event);
    };

  private:
    std::map<std::string, std::unique_ptr<Level>> levels;
    Level* poiner = nullptr;
};

#endif