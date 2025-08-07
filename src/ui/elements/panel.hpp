#pragma once

#include "ui-element.hpp"

#include <iostream>
#include <functional>

class Panel : public UIElement {
	public:
		Panel(
			sf::Texture* panel_texture,
			sf::Vector2f position_coords
		) : texture(std::move(*panel_texture)), position(position_coords) {
			panel = std::make_unique<sf::Sprite>();
			panel->setTexture(texture);
			panel->setScale({ 4,4 });
			panel->setPosition(position);
		};

		std::function<void()> handler = []() {};
		
		inline void setElementPosition(ElementPosition element_position) {
			sf::RenderWindow& window = GameState::instance().getGameWindow();
			switch (element_position) {
				case MiddleCenter:
					panel->setPosition(
						sf::Vector2f(
							{
								(1280 - panel->getGlobalBounds().width) / 2.0f,
								(720 - panel->getGlobalBounds().height) / 2.0f,
							}
						)
					);
					break;
			}
		};

		inline sf::Vector2f getElementPosition() const { return panel->getPosition(); };
		inline sf::Sprite& getButtonSprite() const { return *panel; };

		inline void setIndex(unsigned __int8 new_z_index) override { zIndex = new_z_index; };
		inline unsigned __int8 getIndex() const override { return zIndex; };
		inline void setVisible(bool state) override { isVisible = state; };
		inline bool getVisible() const override { return isVisible; };
		inline void setHandleEvent(std::function<void()> new_handler) override { if (new_handler) handler = new_handler; };
		inline void handleEvent(sf::Event& event, sf::RenderWindow& window) override { if (handler) handler(); };
		inline void render(sf::RenderWindow& window) const override { window.draw(*panel); };

	private:
		std::unique_ptr<sf::Sprite> panel;
		sf::Texture& texture;
		sf::Vector2f position;
		bool isVisible = true;
		unsigned __int8 zIndex;
};