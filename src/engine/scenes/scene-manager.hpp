#pragma once
#ifndef ENGINE_SCENE_MANAGER_H
#define ENGINE_SCENE_MANAGER_H

#include <map>
#include <iostream>
#include <algorithm>
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#if defined(DEBUG)
#include <logger.h>
#endif

class SceneManager {
  public:
    inline bool addScene(const std::string& name, std::unique_ptr<Scene> scene) {
      if (!scene) return false;

      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
      [](unsigned char c) {return std::tolower(c); });

      if (!getScene(copy)) {
        scenes.emplace(copy, std::move(scene));
        return true;
      }; return false;
    };

    inline bool setPointer(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
      [](unsigned char c) {return std::tolower(c); });

      auto lvl = getScene(copy);
      if (lvl) {
        pointer = lvl;
        #if defined(DEBUG)
        LOGO("Changed scene: %s", copy.c_str());
        #endif
        return true;
      }; return false;
    };

    inline Scene* getScene(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(), 
      [](unsigned char c) {return std::tolower(c); });

      auto lvl = scenes.find(copy);
      return (lvl != scenes.end()) ? lvl->second.get() : nullptr;
    };

    inline bool removeScene(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
      [](unsigned char c) {return std::tolower(c); });

      auto lvl = scenes.find(copy);
      if (lvl != scenes.end()) {
        if (pointer) {
          if (pointer == lvl->second.get()) pointer = nullptr;
        }; scenes.erase(lvl);
        return true;
      }; return false;
    };

    inline Scene* getPointer(void) const { return pointer; };

    inline void update(sf::RenderWindow& window, sf::Event& event) {
      if (scenes.empty()) return;
      if (pointer) pointer->update(window, event);
    };

  private:
    std::map<std::string, std::unique_ptr<Scene>> scenes;
    Scene* pointer = nullptr;
};

#endif