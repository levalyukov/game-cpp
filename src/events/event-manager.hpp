#pragma once

#include "Event.hpp"
#include "events/passerby.hpp"
#include <functional>

class EventManager {
	public:
		EventManager() {
			addEvent("test-1", { []() {std::cout << "\n---\nLambda #1;\n---\n"; }, 1.0f });
			addEvent("test-2", { []() {std::cout << "\n---\nLambda #2;\n---\n"; }, 1.5f });
			addEvent("test-3", { []() {std::cout << "\n---\nLambda #3;\n---\n"; }, 5.0f, true });
		}

		struct EventConfig {
			std::function<void()> lambda;
			float delay;
			bool repeat = false;

			float next_trigger = 0.f;
			bool triggered = false;
		};

		std::unordered_map<std::string, EventConfig> events;
		sf::Clock clock;

		inline void addEvent(const std::string name, const EventConfig event) {
			std::string lower_case = name;
			std::transform(lower_case.begin(), lower_case.end(), lower_case.begin(),
				[](unsigned char c) {return std::tolower(c); });
			if (getEvent(lower_case) == nullptr) {
				EventConfig new_event = event;
				new_event.next_trigger = event.delay;
				events.emplace(lower_case, new_event);
			}; 
		};

		inline EventConfig* getEvent(const std::string name) {
			std::string lower_case = name;
			std::transform(lower_case.begin(), lower_case.end(), lower_case.begin(),
				[](unsigned char c) {return std::tolower(c); });
			auto item = events.find(lower_case);
			return (item != events.end()) ? &item->second : nullptr;
		};
		
		inline void removeEvent(const std::string name) {
			std::string lower_case = name;
			std::transform(lower_case.begin(), lower_case.end(), lower_case.begin(),
				[](unsigned char c) {return std::tolower(c); });
			auto item = events.find(lower_case);
			if (item != events.end()) events.erase(item);
		};
		
		inline void update(const float delta) {
			float time = clock.getElapsedTime().asSeconds();
			for (auto& event : events) {
				EventConfig& config = event.second;
				float current_time = clock.getElapsedTime().asSeconds();
				if (config.repeat) {
					if (current_time >= config.next_trigger) {
						config.lambda();
						config.next_trigger = current_time + config.delay;
					};
				} else {
					if (!config.triggered && current_time >= config.next_trigger) {
						config.triggered = true;
						config.lambda();
					};
				};
			};
		};
};