#pragma once

#include "../../core/globals.hpp"
#include "../../ui/ui-manager.hpp"
#include "../../core/resources/resources.hpp"
#include "../screens/hud.hpp"

class KitchenMenu {
	public:
		KitchenMenu();
		~KitchenMenu() {};
		KitchenMenu(KitchenMenu& const) = delete;
		KitchenMenu& operator=(KitchenMenu& const) = delete;

		inline static KitchenMenu& instance() {
			static KitchenMenu km;
			return km;
		}

		inline bool getVisible() const { return visible; };
		inline void setVisible(bool _state) { 
			visible = _state; 
			changeElementVisible(); 
		};
		inline void changeElementVisible() {
			uiManager.getElement("kitchen-ui-background")->setVisible(visible);
			uiManager.getElement("kitchen-ui-panel")->setVisible(visible);
			uiManager.getElement("kitchen-ui-close-button")->setVisible(visible);
		};

	private:
		bool visible = false;

		void initResources();
		void initElements();
		void initElementsPosition();
		void initVisible();
		void initLambdas();

		Globals& globals = Globals::instance();
		sf::RenderWindow& window = globals.getWindow();
		ResourceManager& resourceManager = ResourceManager::instance();
		UIManager& uiManager = UIManager::instance();
};