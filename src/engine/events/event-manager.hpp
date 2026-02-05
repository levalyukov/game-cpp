#pragma once
#ifndef ENGINE_EVENT_MANAGER_H
#define ENGINE_EVENT_MANAGER_H

#include <map>
#include <cmath>
#include <stdint.h>
#include <algorithm>
#include <functional>
#include <SFML/Graphics.hpp>

struct Event_t {
  std::function<void()> lambda;
  uint32_t frequency;
  bool repeat = false;
  uint32_t time = 0;
  bool performed = false;

  Event_t() = default;
  Event_t(
    std::function<void()> _lambda,
    uint32_t _frequency, 
    bool _repeat
  ) : lambda(_lambda), 
      frequency(_frequency),
      repeat(_repeat) {};
};

class EventManager {
  public:
    inline bool addEvent(const std::string& name, std::unique_ptr<Event_t> event) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      if (!getEvent(copy)) {
        event->time = event->frequency + (delay - timer->getElapsedTime().asSeconds());
        events.emplace(copy, std::move(event));
        return true;
      }; return false;
    };

    inline Event_t* getEvent(const std::string& name) const {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      auto event = events.find(copy);
      return (event != events.end()) ? event->second.get() : nullptr;
    };

    inline bool removeEvent(const std::string& name) {
      std::string copy = name;
      std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c) {return std::tolower(c); });

      auto event = events.find(copy);
      if (event != events.end()) {
        events.erase(event);
        return true;
      }; return false;
    };

    inline void update(void) {
      if (events.empty()) return;
      if (!timer) return;

      if (timer->getElapsedTime().asSeconds() >= delay) {
        for (auto& event : events) {
          if (event.second->time == 0) {

            if (!event.second->performed) {
              event.second->lambda();
              event.second->performed = true;
            };

            if (event.second->repeat) {
              event.second->performed = false;
              event.second->time = event.second->frequency;
            } else event.second->performed = true;

          }; event.second->time--;
        }; delay++;
      };
    };
  private:
    uint64_t delay = 0;
    std::map<std::string, std::unique_ptr<Event_t>> events;
    std::unique_ptr<sf::Clock> timer = std::make_unique<sf::Clock>();
};

#endif