#pragma once

#include "../core/resources/resources.hpp"
#include "../ui/ui-manager.hpp"
#include "../entities/entity-manager.hpp"
#include "../entities/entities/build.hpp"
#include "../mechanics/cooking-manager.hpp"

#define DISTANCE_FOR_INTERACTION 125

class Builds {
	public:
		inline void create(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			UIManager& uiManager,
			CookingManager& cookingManager
		) {
			initResources(resourceManager);
			initBuilds(entityManager, resourceManager, uiManager, cookingManager);
			initParameters(entityManager, resourceManager, uiManager, cookingManager);
		};

	private:
		inline void initResources(ResourceManager& resourceManager) {
			resourceManager.loadTexture("kitchen", "../../../assets/textures/entity/builds/kitchen/kitchen.png");
			resourceManager.loadTexture("warehouse", "../../../assets/textures/entity/builds/warehouse/warehouse.png");
		};

		inline void initBuilds(
			EntityManager& entityManager, 
			ResourceManager& resourceManager, 
			UIManager& uiManager, 
			CookingManager& cookingManager
		) {
			entityManager.addEntity("kitchen", std::make_unique<Build>(resourceManager.getTexture("kitchen"), sf::Vector2f({ 512.f,512.f }), sf::Vector2i({ 16,16 })));
			entityManager.addEntity("warehouse", std::make_unique<Build>(resourceManager.getTexture("warehouse"), sf::Vector2f({ 640.f,640.f }), sf::Vector2i({ 16,16 })));
		};

		inline void initParameters(
			EntityManager& entityManager,
			ResourceManager& resourceManager,
			UIManager& uiManager,
			CookingManager& cookingManager
		) {
			initKitchen(entityManager, uiManager, cookingManager);
			initWarehouse(entityManager, uiManager);
		};

		inline void initKitchen(
			EntityManager& entityManager,
			UIManager& uiManager, 
			CookingManager& cookingManager
		) {
			auto kitchen = static_cast<Build*>(entityManager.getEntity("kitchen"));
			kitchen->setHandler(
				[&]() {
					if (Globals::instance().getUIOpened()) return;
					auto player = static_cast<Player*>(entityManager.getEntity("player"));
					auto build = static_cast<Build*>(entityManager.getEntity("kitchen"));
					if (entityManager.getDistance(build->getSprite(), player->getSprite()) <= DISTANCE_FOR_INTERACTION) {
						if (!cookingManager.getCookeedFlag() && !cookingManager.getCookingFlag()) {
							Globals::instance().setUIOpened(true);
							uiManager.getElement("kitchen-ui-background")->setVisible(true);
							uiManager.getElement("kitchen-ui-panel")->setVisible(true);
							uiManager.getElement("kitchen-ui-close-button")->setVisible(true);
							for (int y = 0; y < cookingManager.availableRecipes.size(); y++) {
								std::string buttonRecipe = "kitchen-ui-recipe-button-" + std::to_string(y);
								std::string buttonLabelRecipe = "kitchen-ui-recipe-button-" + std::to_string(y) + "-label";
								if (uiManager.getElement(buttonRecipe) && uiManager.getElement(buttonLabelRecipe)) {
									uiManager.getElement(buttonRecipe)->setVisible(true);
									uiManager.getElement(buttonLabelRecipe)->setVisible(true);
								};
							};
						} else if (cookingManager.getCookeedFlag()) {
							cookingManager.resetCookeedFlag();
						};
					};
				}
			);
		};

		inline void initWarehouse(
			EntityManager& entityManager,
			UIManager& uiManager
		) {
			auto warehouse = static_cast<Build*>(entityManager.getEntity("warehouse"));
			warehouse->setHandler(
				[&]() {
					if (Globals::instance().getUIOpened()) return;

					auto player = static_cast<Player*>(entityManager.getEntity("player"));
					auto build = static_cast<Build*>(entityManager.getEntity("warehouse"));
					if (entityManager.getDistance(build->getSprite(), player->getSprite()) <= DISTANCE_FOR_INTERACTION) {
						if (!uiManager.getElement("warehouse-background")) return;
						if (!uiManager.getElement("warehouse-panel")) return;

						Globals::instance().setUIOpened(true);
						uiManager.getElement("warehouse-background")->setVisible(true);
						uiManager.getElement("warehouse-panel")->setVisible(true);
						uiManager.getElement("warehouse-close-button")->setVisible(true);
					};
				}
			);
		};
};