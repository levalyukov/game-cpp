#pragma once
#ifndef ENGINE_ENTITY_MANAGER_H
#define ENGINE_ENTITY_MANAGER_H

#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include "entity.hpp"

class EntityManager {
	public:
    inline bool addEntity(const std::string& name, std::unique_ptr<Entity> entity) {
      if (!entity) return false;

      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(), 
      [](unsigned char c) {return std::tolower(c); });
      
      if (!getEntity(copy)) {
        entitiesSort.emplace_back(entity.get());
        entities.emplace(copy, std::move(entity));
        return true;
      }; return false;
    };

    inline Entity* getEntity(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
      [](unsigned char c) {return std::tolower(c); });

      auto entity = entities.find(copy);
      return (entity != entities.end()) ? entity->second.get() : nullptr;
    };

    inline bool removeEntity(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
      [](unsigned char c) {return std::tolower(c); });

      auto entity = entities.find(copy);
      if (entity == entities.end()) return false;

      auto it = std::find(entitiesSort.begin(),
      entitiesSort.end(), entity->second.get());
      if (it == entitiesSort.end()) return false;
      else entitiesSort.erase(it);

      entities.erase(entity);
      return true;
    };

    inline void update(sf::RenderWindow& window, sf::Event& event) {
      if (entities.empty()) return;

      std::sort(entitiesSort.begin(), entitiesSort.end(), 
      [](const Entity* a, const Entity* b) {
          return a->getSprite().getPosition().y < b->getSprite().getPosition().y;
      });

      for (const auto& entity : entities) {
        if (entity.second) entity.second->update(window, event);
      };
    };

	private:
    std::vector<Entity*> entitiesSort;
    std::map<std::string, std::unique_ptr<Entity>> entities;
};

#endif