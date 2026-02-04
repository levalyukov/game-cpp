#pragma once

#include <iostream>
#include <memory>
#include "element.hpp"
#include <functional>
#include "label.hpp"
#if defined(DEBUG)
#include <logger.h>
#endif

class Button : public UIElement {
  public:
    Button(
      sf::Texture* button_texture,
      const sf::Vector2i& button_size,
      const sf::Vector2i& button_position = {0,0}
    ) : texture(*button_texture),
        size(button_size){
      if (!sprite) sprite = std::make_unique<sf::Sprite>();
      sprite->setScale(4, 4);
      sprite->setTexture(texture);
      sprite->setPosition(button_position.x, button_position.y);
      sprite->setTextureRect(sf::IntRect({ 0,0 }, size));
    };

    inline void setFunction(const std::function<void()> lambda) { button = lambda; };
    inline Label& getButtonText(void) const { return *text.get(); };
    inline sf::Sprite& getButton(void) const { return *sprite.get(); };
    inline void setDepth(const int16_t new_depth) override { depth = new_depth; };
    inline int16_t getDepth(void) const override { return depth; };
    inline bool getVisible(void) const override { return visible; };
    inline void setVisible(const bool& new_state) override { visible = new_state; };

    inline bool setButtonText(sf::Font* font, const std::wstring& message) {
      if (!sprite) return false;
      if (!font) return false;

      if (!text) {
        text = std::make_unique<Label>(message, font);
        text->getLabel().setPosition(sprite->getPosition());
        #if defined(DEBUG)
        LOGO("The text for the button has been successfully created.");
        #endif
        return true;
      }; 
      #if defined(DEBUG)
      LOGE("Error when creating the button text.");
      #endif
      return false;
    };

    inline void update(sf::RenderWindow& window, sf::Event& event) override {
      if (sprite) {
        bool hovered = sprite->getGlobalBounds().contains(
          window.mapPixelToCoords(sf::Mouse::getPosition(window)));
       
        if (hovered && state == state_t::NONE) state = state_t::HOVERED;
        if (hovered && state != state_t::PRESSED
        && event.type == sf::Event::MouseButtonPressed
        && event.mouseButton.button == sf::Mouse::Left){
          state = state_t::PRESSED;
          if (!pressed) {
            pressed = true;
            if (button) button();
            #if defined(DEBUG)
            else LOGE("Lambda of the button is invalid.");
            #endif
          };
        }; 
        
        if (event.type == sf::Event::MouseButtonReleased) {
          pressed = false;
          state = state_t::HOVERED;
        }; if (!hovered) state = state_t::NONE;

        sprite->setTextureRect(sf::IntRect({ 0,state * 16 }, size));
        window.draw(*sprite);
      };

      if (text) text->update(window, event);
    };

  private:
    enum state_t {NONE, HOVERED, PRESSED};
    state_t state = state_t::NONE;
    int16_t depth = 0;
    bool visible = true;
    bool pressed = false;

    std::function<void()> button;
    std::unique_ptr<sf::Sprite> sprite = nullptr;
    std::unique_ptr<Label> text = nullptr;
    sf::Texture& texture;
    sf::Vector2i size;
};