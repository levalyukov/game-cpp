#pragma once

#include "../ui/ui-manager.hpp"
#include "../core/resources/resources.hpp"
#include "../entities/entity-manager.hpp"
#include "../entities/entities/build.hpp"

class Builds {
	public:
		Builds() {};

		inline void create(ResourceManager& resourceManager, EntityManager& entityManager, UIManager& uiManager) {
			initResources(resourceManager);
			initBuilds(entityManager, resourceManager, uiManager);
		};

	private:
		inline void initResources(ResourceManager& resourceManager) {
			resourceManager.loadTexture("kitchen", "../../../assets/textures/entity/builds/kitchen/kitchen.png");
		};

		inline void initBuilds(EntityManager& entityManager, ResourceManager& resourceManager, UIManager& uiManager) {
			entityManager.addEntity(
				"kitchen",
				std::make_unique<Build>(
					resourceManager.getTexture("kitchen"),
					sf::Vector2f({ 512.f,512.f }),
					sf::Vector2i({ 16,16 })
				));
			initKitchen(entityManager, uiManager);
		};

		inline void initKitchen(EntityManager& entityManager, UIManager& uiManager) {
			auto kitchen = static_cast<Build*>(entityManager.getEntity("kitchen"));
			kitchen->setHandleEvent(
				[&]() {
					
				}
			);
		};
};