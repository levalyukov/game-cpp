#pragma once

#include <memory>
#include <scenes/scene.hpp>
#include <ui/ui-manager.hpp>
#include <scenes/scene-manager.hpp>
#include <entity/entity-manager.hpp>
#include <events/event-manager.hpp>

class GameMap1 : public Scene {
  public:
    GameMap1(SceneManager* scene_manager) : scenes(*scene_manager) { init(); };

    inline void update(sf::RenderWindow& window, sf::Event& event) override {
      if (ui) ui->update(window, event);
      if (entity) entity->update(window, event);
      if (events) events->update();

      window.clear(sf::Color(255, 105, 180));
      window.display();
    };

  private:
    SceneManager& scenes;
    std::unique_ptr<UIManager> ui = std::make_unique<UIManager>();
    std::unique_ptr<EntityManager> entity = std::make_unique<EntityManager>();
    std::unique_ptr<EventManager> events = std::make_unique<EventManager>();

    void init(void);
};