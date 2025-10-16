#include "progress-bar.hpp"

void ProgressBar::handleEvent(
	sf::Event& event, 
	sf::RenderWindow& window,
	const float delta
) {
	if (!reverse) {
		timer += delta;
		if (counter >= max) process = false;
		if (process) {
			if (timer >= 1.f) {
				counter++;
				timer = 0.f;
				bar->setTextureRect(sf::IntRect(
					sf::Vector2i(0, 0),
					sf::Vector2i(static_cast<int>(size.x * (counter / 100.0)), size.y)
				));
			};
		} else { 
			if (!processed) {
				if (handler) handler();
				processed = true;
			};
		};
	} else {
		timer += delta;
		if (counter <= min) process = false;
		if (process) {
			if (timer >= 1.f) {
				counter--;
				timer = 0.f;
				bar->setTextureRect(sf::IntRect(
					sf::Vector2i(0, 0),
					sf::Vector2i(static_cast<int>(size.x - (size.x - (size.x * counter) / 100.0)), size.y)
				));
			};
		} else {
			if (!processed) {
				if (handler) handler();
				processed = true;
			};
		};
	};
};