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
			resourceManager.loadTexture(
				"bake",	"../../../assets/textures/entity/builds/bake/bake.png");
			resourceManager.loadTexture(
				"fridge",	"../../../assets/textures/entity/builds/fridge/fridge.png");
			resourceManager.loadTexture(
				"trashbox", "../../../assets/textures/entity/builds/trashbox/trashbox.png");
			resourceManager.loadTexture(
				"kitchen", "../../../assets/textures/entity/builds/kitchen/kitchen.png");
		};

		inline void initBuilds(
			EntityManager& entityManager, 
			ResourceManager& resourceManager, 
			UIManager& uiManager, 
			CookingManager& cookingManager
		) {
			if (resourceManager.getTexture("bake")
			&& !entityManager.getEntity("bake")) {
				entityManager.addEntity("bake",
					std::make_unique<Build>(
					resourceManager.getTexture("bake"),
					sf::Vector2f({ 11 * 64,4 * 64 }),
					sf::Vector2i({ 16,32 })
				));
			};
			if (resourceManager.getTexture("fridge") 
			&& !entityManager.getEntity("fridge")) {
				entityManager.addEntity("fridge",
					std::make_unique<Build>(
					resourceManager.getTexture("fridge"),
					sf::Vector2f({ 14 * 64,4 * 64 }),
					sf::Vector2i({ 16,32 })
				));
			};
			if (resourceManager.getTexture("trashbox") 
			&& !entityManager.getEntity("trashbox")) {
				entityManager.addEntity("trashbox",
					std::make_unique<Build>(
					resourceManager.getTexture("trashbox"),
					sf::Vector2f({ 13 * 64,5 * 64 }),
					sf::Vector2i({ 16,16 })
				));
			};
			if (resourceManager.getTexture("kitchen") 
			&& !entityManager.getEntity("kitchen")) {
				entityManager.addEntity("kitchen",
					std::make_unique<Build>(
					resourceManager.getTexture("kitchen"),
					sf::Vector2f({ 16 * 64,5 * 64 }),
					sf::Vector2i({ 32,16 })
				));
			};
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
			initFridge(entityManager, uiManager);
			initTrashbox(entityManager, orderManager, items);
		};

		inline void initKitchen(
			EntityManager& entityManager,
			UIManager& uiManager, 
			CookingManager& cookingManager,
			OrdersManager& orderManager,
			OrdersDisplay& orderDisplay,
			Items& items
		) {
			if (!entityManager.getEntity("bake")) return;
			auto bake = static_cast<Build*>(entityManager.getEntity("bake"));
			bake->setHandler([&entityManager, &cookingManager, &uiManager, &orderManager, &orderDisplay, &items]() {
				if (Globals::instance().getUIOpened()) return;
				auto player = static_cast<Player*>(entityManager.getEntity("player"));
				auto build = static_cast<Build*>(entityManager.getEntity("bake"));
				if (player->getSelectedItem() != 0) return;
				if (entityManager.getDistance(build->getSprite(), player->getSprite()) <= DISTANCE_FOR_INTERACTION) {
					if (!cookingManager.getCookeedFlag() && !cookingManager.getCookingFlag()) {
						Globals::instance().setUIOpened(true);
						uiManager.getElement("bake-ui-background")->setVisible(true);
						uiManager.getElement("bake-ui-panel")->setVisible(true);
						uiManager.getElement("bake-ui-close-button")->setVisible(true);
						for (int y = 0; y < cookingManager.availableRecipes.size(); y++) {
							std::string buttonRecipe = "bake-ui-recipe-button-" + std::to_string(y);
							std::string buttonLabelRecipe = "bake-ui-recipe-button-" + std::to_string(y) + "-label";
							if (uiManager.getElement(buttonRecipe) && uiManager.getElement(buttonLabelRecipe)) {
								uiManager.getElement(buttonRecipe)->setVisible(true);
								uiManager.getElement(buttonLabelRecipe)->setVisible(true);
							};
						};
					} else if (cookingManager.getCookeedFlag() && entityManager.getEntity("player")) {
						if (player->getSelectedItem() != 0) return;
						player->setSelectedItem(cookingManager.getRecipe(cookingManager.getCookingRecipeName())->id, items);
						cookingManager.resetCookeedFlag();
						if (orderManager.orders.empty()) return;
						for (auto& order : orderManager.orders) {
							if (orderManager.getOrder(order.first)->id == player->getSelectedItem()) {
								orderManager.getOrder(order.first)->cookeed = true;
								break;
							};
						}; orderDisplay.update();
					};
				};
			});
		};

		inline void initFridge(
			EntityManager& entityManager,
			UIManager& uiManager
		) {
			if (!entityManager.getEntity("fridge")) return;
			auto fridge = static_cast<Build*>(entityManager.getEntity("fridge"));
			fridge->setHandler([&entityManager, &uiManager]() {
				if (Globals::instance().getUIOpened()) return;

				auto player = static_cast<Player*>(entityManager.getEntity("player"));
				auto build = static_cast<Build*>(entityManager.getEntity("fridge"));
				if (entityManager.getDistance(build->getSprite(), player->getSprite()) <= DISTANCE_FOR_INTERACTION) {
					if (!uiManager.getElement("fridge-background")) return;
					if (!uiManager.getElement("fridge-panel")) return;
					if (!uiManager.getElement("fridge-close-button")) return;

					Globals::instance().setUIOpened(true);
					uiManager.getElement("fridge-background")->setVisible(true);
					uiManager.getElement("fridge-panel")->setVisible(true);
					uiManager.getElement("fridge-close-button")->setVisible(true);
				};
			});
		};

		inline void initTrashbox(
			EntityManager& entityManager,
			OrdersManager& orderManager,
			Items& items
		) {
			if (!entityManager.getEntity("player")) return;
			if (!entityManager.getEntity("trashbox")) return;
			auto trashbox = static_cast<Build*>(entityManager.getEntity("trashbox"));
			trashbox->setHandler([&entityManager, &items, &orderManager]() {
				auto player = static_cast<Player*>(entityManager.getEntity("player"));
				bool correspondingOrder = false;

				for (const auto& order : orderManager.orders) {
					if (order.second.cookeed && order.second.id == player->getSelectedItem()) {
						correspondingOrder = true;
						break;
					};
				};

				if (!correspondingOrder && player->getSelectedItem() != 0) 
					player->setSelectedItem(0, items);
			});
 		};
};