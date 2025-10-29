#pragma once

#include "../core/resources/resources.hpp"
#include "../entities/entity-manager.hpp"
#include "../entities/entities/build.hpp"
#include "../mechanics/cooking-manager.hpp"
#include "../ui/screens/orders.hpp"
#include "../ui/ui-manager.hpp"

#define DISTANCE_FOR_INTERACTION 125

class Builds {
	public:
		inline void create(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			UIManager& uiManager,
			CookingManager& cookingManager,
			OrdersManager& orderManager,
			OrdersDisplay& orderDisplay,
			Items& items
		) {
			initResources(resourceManager);
			initBuilds(entityManager, resourceManager, uiManager, cookingManager);
			initParameters(entityManager, resourceManager, uiManager, cookingManager, orderManager, orderDisplay, items);
		};

	private:
		inline void initResources(ResourceManager& resourceManager) {
			resourceManager.loadTexture("kitchen", "../../../assets/textures/entity/builds/kitchen/kitchen.png");
			resourceManager.loadTexture("warehouse", "../../../assets/textures/entity/builds/warehouse/warehouse.png");
			resourceManager.loadTexture("trashbox", "../../../assets/textures/entity/builds/trashbox/trashbox.png");
		};

		inline void initBuilds(
			EntityManager& entityManager, 
			ResourceManager& resourceManager, 
			UIManager& uiManager, 
			CookingManager& cookingManager
		) {
			entityManager.addEntity("kitchen", std::make_unique<Build>(resourceManager.getTexture("kitchen"), sf::Vector2f({ 512.f,512.f }), sf::Vector2i({ 16,16 })));
			entityManager.addEntity("warehouse", std::make_unique<Build>(resourceManager.getTexture("warehouse"), sf::Vector2f({ 640.f,640.f }), sf::Vector2i({ 16,16 })));
			entityManager.addEntity("trashbox", std::make_unique<Build>(resourceManager.getTexture("trashbox"), sf::Vector2f({ 740.f,740.f }), sf::Vector2i({ 16,16 })));
		};

		inline void initParameters(
			EntityManager& entityManager,
			ResourceManager& resourceManager,
			UIManager& uiManager,
			CookingManager& cookingManager,
			OrdersManager& orderManager,
			OrdersDisplay& orderDisplay,
			Items& items
		) {
			initKitchen(entityManager, uiManager, cookingManager, orderManager, orderDisplay, items);
			initWarehouse(entityManager, uiManager);
			initTrashbox(entityManager, items);
		};

		inline void initKitchen(
			EntityManager& entityManager,
			UIManager& uiManager, 
			CookingManager& cookingManager,
			OrdersManager& orderManager,
			OrdersDisplay& orderDisplay,
			Items& items
		) {
			if (!entityManager.getEntity("kitchen")) return;
			auto kitchen = static_cast<Build*>(entityManager.getEntity("kitchen"));
			kitchen->setHandler([&]() {
				if (Globals::instance().getUIOpened()) return;
				auto player = static_cast<Player*>(entityManager.getEntity("player"));
				auto build = static_cast<Build*>(entityManager.getEntity("kitchen"));
				if (player->getSelectedItem() != 0) return;
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
					} else if (cookingManager.getCookeedFlag() && entityManager.getEntity("player")) {
						if (player->getSelectedItem() != 0) return;
						player->setSelectedItem(cookingManager.getRecipe(cookingManager.getCookingRecipeName())->id, items);
						if (orderManager.orders.empty()) return;
						for (auto& order : orderManager.orders) {
							if (orderManager.getOrder(order.first)->id == player->getSelectedItem()) {
								orderManager.getOrder(order.first)->cookeed = true;
								break;
							};
						}; orderDisplay.update();
						cookingManager.resetCookeedFlag();
					};
				};
			});
		};

		inline void initWarehouse(
			EntityManager& entityManager,
			UIManager& uiManager
		) {
			if (!entityManager.getEntity("warehouse")) return;
			auto warehouse = static_cast<Build*>(entityManager.getEntity("warehouse"));
			warehouse->setHandler([&]() {
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
			});
		};

		inline void initTrashbox(
			EntityManager& entityManager,
			Items& items
		) {
			if (!entityManager.getEntity("player")) return;
			if (!entityManager.getEntity("trashbox")) return;
			auto trashbox = static_cast<Build*>(entityManager.getEntity("trashbox"));
			trashbox->setHandler([&]() {
				auto player = static_cast<Player*>(entityManager.getEntity("player"));
				if (player->getSelectedItem() != 0) {
					player->setSelectedItem(0, items);
				};
			});
 		};
};