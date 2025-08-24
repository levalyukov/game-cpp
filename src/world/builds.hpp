#pragma once

#include "../ui/ui-manager.hpp"
#include "../core/resources/resources.hpp"
#include "../entities/entity-manager.hpp"
#include "../entities/entities/build.hpp"

#include "../ui/screens/hud.hpp"
#include "../ui/screens/kitchen.hpp"

#include <iostream>

class Builds {
	public:
		inline static Builds& instance() {
			static Builds b;
			return b;
		};

		inline void create(ResourceManager& resourceManager, EntityManager& entityManager) {
			initResources(resourceManager);
			initBuilds(entityManager, resourceManager);
		};

	private:
		Builds() {};
		~Builds() {};
		Builds(Builds& const) = delete;
		Builds& operator=(Builds& const) = delete;
		UIManager& uiManager = UIManager::instance();

		inline void initResources(ResourceManager& resourceManager) {
			resourceManager.loadTexture("kitchen", "../../../assets/textures/entity/builds/kitchen/kitchen.png");
		};

		inline void initBuilds(EntityManager& entityManager, ResourceManager& resourceManager) {
			entityManager.addEntity(
				"kitchen",
				std::make_unique<Build>(
					resourceManager.getTexture("kitchen"),
					sf::Vector2f({ 256.f,256.f }),
					sf::Vector2i({ 16,16 })
				));
			initKitchen(entityManager);
		};

		inline void initKitchen(EntityManager& entityManager) {
			auto kitchen = static_cast<Build*>(entityManager.getEntity("kitchen"));
			kitchen->setHandleEvent([]() {
				KitchenMenu& kitchen = KitchenMenu::instance();
				UIManager& uiManager = UIManager::instance();
				HUD& hud = HUD::instance();
				if (!kitchen.getVisible()) {
					kitchen.setVisible(true);
					hud.setVisible(false);
				}
			});
		};
};