#pragma once

#include "ui-element.hpp"

#include <iostream>
#include <functional>

class ProgressBar : public UIElement {
	public:
		ProgressBar(
			sf::Texture* bar_texture,
			sf::Vector2i bar_size
		) : texture(std::move(*bar_texture)),
			size(bar_size) {
			bar = std::make_unique<sf::Sprite>();
			if (!bar) return;
			bar->setTexture(texture);
			bar->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size));
			bar->setScale(4, 4);
		};

		std::function<void()> handler;

		inline float getMaxValue() const { return max; };
		inline float getMinValue() const { return min; };
		inline void setValues(float max_val = 100.f, float min_val = 0.f) { max = max_val; min = min_val; counter = max; };
		inline void setMode(bool state) { reverse = state; };
		inline sf::Sprite& getSprite() const { return *bar; };
		inline void setSortIndex(uint8_t new_depth) override { depth = new_depth; };
		inline uint8_t getSortIndex() const override { return depth; };
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handler) { handler = new_handler; };
		void handleEvent(sf::Event& event, sf::RenderWindow& window, const float delta) override;
		inline void render(sf::RenderWindow& window) const override { if (bar) window.draw(*bar); };

	private:
		std::unique_ptr<sf::Sprite> bar = nullptr;
		sf::Texture& texture;
		sf::Vector2i size;

		float executionStep = 0;
		bool trigger = false;
		bool process = true; 
		bool reverse = false;
		float max = 100.f;
		float min = 0.f;
		float counter = 0.f;
		float timer = 0.f;

		bool isVisible = true;
		uint8_t depth = 0;
};