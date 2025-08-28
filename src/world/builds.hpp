#pragma once

#include "../ui/ui-manager.hpp"
#include "../core/resources/resources.hpp"
#include "../entities/entity-manager.hpp"
#include "../mechanics/cooking.hpp"
#include "../entities/entities/build.hpp"

class Builds {
	public:
		Builds() {};

		inline void create(ResourceManager& resourceManager, EntityManager& entityManager, UIManager& uiManager, CookingManager& cookingManager) {
			initResources(resourceManager);
			initBuilds(entityManager, resourceManager, uiManager, cookingManager);
		};

	private:
		inline void initResources(ResourceManager& resourceManager) {
			resourceManager.loadTexture("kitchen", "../../../assets/textures/entity/builds/kitchen/kitchen.png");
		};

		inline void initBuilds(EntityManager& entityManager, ResourceManager& resourceManager, UIManager& uiManager, CookingManager& cookingManager) {
			entityManager.addEntity(
				"kitchen",
				std::make_unique<Build>(
					resourceManager.getTexture("kitchen"),
					sf::Vector2f({ 512.f,512.f }),
					sf::Vector2i({ 16,16 })
				));
			initKitchen(entityManager, uiManager, cookingManager);
		};

		inline void initKitchen(EntityManager& entityManager, UIManager& uiManager, CookingManager& cookingManager) {
			auto kitchen = static_cast<Build*>(entityManager.getEntity("kitchen"));
			kitchen->setHandleEvent(
				[&]() {
					uiManager.getElement("kitchen-ui-background")->setVisible(true);
					uiManager.getElement("kitchen-ui-panel")->setVisible(true);
					uiManager.getElement("kitchen-ui-close-button")->setVisible(true);
					for (int y = 0; y < cookingManager.recipes.size(); y++) {
						std::string buttonRecipe = "kitchen-ui-recipe-button-" + std::to_string(y);
						std::string buttonLabelRecipe = "kitchen-ui-recipe-button-" + std::to_string(y) + "-label";
						if (uiManager.getElement(buttonRecipe) && uiManager.getElement(buttonLabelRecipe)) {
							uiManager.getElement(buttonRecipe)->setVisible(true);
							uiManager.getElement(buttonLabelRecipe)->setVisible(true);
						}
					}
				}
			);
		};
};