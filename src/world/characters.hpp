#pragma once


#include "../core/animations/animations.hpp"
#include "../core/resources/resources.hpp"
#include "../mechanics/economy-manager.hpp"
#include "../entities/entity-manager.hpp"
#include "../entities/entities/player.hpp"
#include "../entities/entities/npc.hpp"
#include "../ui/screens/hud.hpp"
#include "../core/utils.hpp"
#include "../mechanics/items.hpp"

#include <vector>
#include <stdint.h>

class Characters {
	public:
		std::vector<sf::Vector2f> passerbyMovement = {
			sf::Vector2f(0,8 * 64), sf::Vector2f(0,8 * 64 + 48), sf::Vector2f(0,8 * 64 + 32), sf::Vector2f(0,8 * 64 -32),
			sf::Vector2f(25 * 64,8 * 64), sf::Vector2f(25 * 64,8 * 64 + 48), sf::Vector2f(25 * 64,8 * 64 + 32), sf::Vector2f(0,8 * 64 -32),
		};

		std::vector<sf::Vector2f> customerMovement = {
			sf::Vector2f(25 * 64,8 * 64), sf::Vector2f(12 * 64,8 * 64), sf::Vector2f(12 * 64,7 * 64), // Movement to the restaurant
			sf::Vector2f(0 * 64,8 * 64)
		};

		inline void spawn(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			EconomyManager& economyManager,
			HUD& hud
		) {
			player(resourceManager, entityManager);
		};

		inline void passerby(
			ResourceManager& resourceManager,
			EntityManager& entityManager
		) {
			std::string new_npc_id = generetingNewPasserbyID(entityManager);
			initNPCResources(resourceManager, new_npc_id);
			spawnPasserby(resourceManager, entityManager, new_npc_id);
			setPasserbyEvent(resourceManager, entityManager, new_npc_id);
		};

		inline void customer(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			OrdersManager& orderManager,
			EventManager& eventManager,
			OrdersDisplay& ordersDisplay,
			Items& items
		) {
			if (!hasCustomer) {
				std::string new_customer_id = generetingNewCustomerID(entityManager);
				initNPCResources(resourceManager, new_customer_id);
				spawnCustomer(resourceManager, entityManager, new_customer_id);
				setCustomerEvent(resourceManager, entityManager, orderManager, eventManager, ordersDisplay, items, new_customer_id);
				setCustomerHandle(resourceManager, entityManager, orderManager, ordersDisplay, items, new_customer_id);
				hasCustomer = true;
			};
		};

	private:
		Utils utils;
		const int DELETE_PASSERBY = 1000;
		bool hasCustomer = false;

		inline float getDirection() {
			if (utils.rangeRandom(0, 1) == 0) return -WALK_SPEED;
			else return WALK_SPEED;
		};

		inline sf::Vector2i getVector(const float direction) {
			if (direction < 0) return sf::Vector2i(0, 0);
			else return sf::Vector2i(0, 16);
		};

		inline std::string generetingNewPasserbyID(EntityManager& entityManager) {
			uint16_t id = 0;
			uint16_t gen_id = 0;
			uint16_t attempts = 0;
			while (attempts < 10) {
				gen_id = utils.rangeRandom(1, 3);
				if (entityManager.getEntity("npc-" + std::to_string(gen_id))) attempts++;
				else { id = gen_id; break; };
			}; return std::to_string(id);
		};

		inline std::string generetingNewCustomerID(EntityManager& entityManager) {
			uint16_t id = 0;
			uint16_t gen_id = 0;
			uint16_t attempts = 0;
			while (attempts < 10) {
				gen_id = utils.rangeRandom(1, 2);
				if (entityManager.getEntity("npc-customer-" + std::to_string(gen_id))) attempts++;
				else { id = gen_id; break; };
			}; return std::to_string(id);
		};

		inline sf::Vector2f getPasserbyPosition(const float direction) {
			sf::Vector2i vector;
			std::random_device rd;
			std::mt19937 rand(rd());
			if (direction > 0) vector = { 0, 3 };
			else vector = { 4,static_cast<int>(passerbyMovement.size() - 1)};
			std::uniform_int_distribution<int> dist(vector.x, vector.y);
			return passerbyMovement[dist(rd)];
		};

		inline uint8_t getNewOrder(Items& items) {
			std::random_device rd; 
			std::mt19937 rand(rd());
			std::uniform_int_distribution<int> dist(1, items.getAllRecipes());
			return static_cast<uint8_t>(dist(rd));
		};

		inline void player(ResourceManager& resourceManager, EntityManager& entityManager) const {
			resourceManager.loadTexture("character-idle", "../../../assets/textures/entity/player/character-idle.png");
			resourceManager.loadTexture("character-walk-horizontal", "../../../assets/textures/entity/player/character-walk-horizontal.png");
			resourceManager.loadTexture("character-walk-vertical", "../../../assets/textures/entity/player/character-walk-vertical.png");
			resourceManager.loadTexture("character-item-idle", "../../../assets/textures/entity/player/character-item-idle.png");
			resourceManager.loadTexture("character-walk-item-horizontal", "../../../assets/textures/entity/player/character-walk-item-horizontal.png");
			resourceManager.loadTexture("character-walk-item-vertical", "../../../assets/textures/entity/player/character-walk-item-vertical.png");
			resourceManager.loadTexture("entity-shadow", "../../../assets/textures/entity/entity-shadow.png");

			entityManager.addEntity(
				"player",
				std::make_unique<Player>(
					resourceManager.getTexture("character-idle"),
					resourceManager.getTexture("character-walk-horizontal"),
					resourceManager.getTexture("character-walk-vertical"),
					resourceManager.getTexture("character-item-idle"),
					resourceManager.getTexture("character-walk-item-horizontal"),
					resourceManager.getTexture("character-walk-item-vertical"),
					resourceManager.getTexture("entity-shadow")
			));
		};

		inline void initNPCResources(
			ResourceManager& resourceManager,
			const std::string npc_id
		) {
			if (resourceManager.getTexture("npc-" + npc_id + "-idle")) return;
			if (resourceManager.getTexture("npc-" + npc_id + "-walk-horizontal")) return;
			if (resourceManager.getTexture("npc-" + npc_id + "-walk-vertical")) return;

			resourceManager.loadTexture("npc-" + npc_id + "-idle", "../../../assets/textures/entity/npc/npc-" + npc_id + "-idle.png");
			resourceManager.loadTexture("npc-" + npc_id + "-walk-horizontal", "../../../assets/textures/entity/npc/npc-" + npc_id + "-movement-horizontal.png");
			resourceManager.loadTexture("npc-" + npc_id + "-walk-vertical", "../../../assets/textures/entity/npc/npc-" + npc_id + "-movement-vertical.png");
		};
		
		inline void spawnPasserby(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			const std::string npc_id
		) {
			if (!resourceManager.getTexture("npc-" + npc_id + "-idle")) return;
			if (!resourceManager.getTexture("npc-" + npc_id + "-walk-vertical")) return;
			if (!resourceManager.getTexture("npc-" + npc_id + "-walk-horizontal")) return;

			entityManager.addEntity(
				"npc-" + npc_id,
				std::make_unique<NPC>(
					resourceManager.getTexture("npc-" + npc_id + "-idle"),
					resourceManager.getTexture("npc-" + npc_id + "-walk-vertical"),
					resourceManager.getTexture("npc-" + npc_id + "-walk-horizontal"),
					resourceManager.getTexture("entity-shadow")
			));
		};

		inline void spawnCustomer(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			const std::string npc_id
		) {
			if (!resourceManager.getTexture("npc-" + npc_id + "-idle")) return;
			if (!resourceManager.getTexture("npc-" + npc_id + "-walk-vertical")) return;
			if (!resourceManager.getTexture("npc-" + npc_id + "-walk-horizontal")) return;

			entityManager.addEntity(
				"npc-customer-" + npc_id,
				std::make_unique<NPC>(
					resourceManager.getTexture("npc-" + npc_id + "-idle"),
					resourceManager.getTexture("npc-" + npc_id + "-walk-vertical"),
					resourceManager.getTexture("npc-" + npc_id + "-walk-horizontal"),
					resourceManager.getTexture("entity-shadow")
				));
		};

		inline void setPasserbyEvent(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			const std::string npc_id
		) {
			std::string npcName = "npc-" + npc_id;
			if (!entityManager.getEntity(npcName)) return;

			auto passerby = entityManager.getEntity(npcName);
			auto player = static_cast<Player*>(entityManager.getEntity("player"));
			float direction = getDirection();
			sf::Vector2i vector = getVector(direction);
			static_cast<NPC*>(passerby)->getSprite().setPosition(getPasserbyPosition(direction));
			passerby->setEvent([this, npcName, passerby, direction, vector, &entityManager]() {
				auto npc = static_cast<NPC*>(passerby);
				auto player = (entityManager.getEntity("player")) ? static_cast<Player*>(entityManager.getEntity("player")) : nullptr;
				static float time = 0.f;
				npc->getSprite().move({ static_cast<float>(direction - (direction * 0.5)),0 });
				npc->getAnimation().update(npc->getSprite(), npc->getTextureMoveHorizontal(), vector, {16,16}, WALK_ANIM, 3, npc->getDelta());
				if (player) {
					if (entityManager.getDistance(player->getSprite(), npc->getSprite()) > DELETE_PASSERBY) {
						entityManager.removeEntity(npcName);
					};
				};
			});
		};

		inline void setCustomerEvent(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			OrdersManager& orderManager,
			EventManager& eventManager,
			OrdersDisplay& ordersDisplay,
			Items& items,
			const std::string npc_id
		) {
			std::string npcName = "npc-customer-" + npc_id;
			if (!entityManager.getEntity(npcName)) return;

			auto customer = static_cast<NPC*>(entityManager.getEntity(npcName));
			float direction = getDirection();
			sf::Vector2i vector = getVector(direction);
			customer->getSprite().setPosition(customerMovement[0]);
			customer->setOrder(getNewOrder(items));

			auto movement_flags = std::make_shared<std::pair<bool, bool>>(false, false);
			entityManager.getEntity(npcName)->setEvent([this, npcName, movement_flags, npc_id, &entityManager, &eventManager, &orderManager, &ordersDisplay, &items]() {
				auto customer_npc = (entityManager.getEntity(npcName)) ? static_cast<NPC*>(entityManager.getEntity(npcName)) : nullptr;
				float move_speed = static_cast<float>(-WALK_SPEED - (-WALK_SPEED * 0.5));

				if (!movement_flags->first) {
					if (customer_npc->getSprite().getPosition() != customerMovement[1]) {
						customer_npc->getSprite().move(move_speed, 0);
						customer_npc->getAnimation().update(
							customer_npc->getSprite(),
							customer_npc->getTextureMoveHorizontal(),
							{ 0,0 }, { 16,16 },
							WALK_ANIM, 3, customer_npc->getDelta()
						);
					} else movement_flags->first = true;
				};

				if (movement_flags->first && !movement_flags->second) {
					if (customer_npc->getSprite().getPosition() != customerMovement[2]) {
						customer_npc->getSprite().move(0, move_speed);
						customer_npc->getAnimation().update(
							customer_npc->getSprite(),
							customer_npc->getTextureMoveVertical(),
							{ 0,16 }, { 16,16 },
							WALK_ANIM, 3, customer_npc->getDelta()
						);
					} else {
						movement_flags->second = true;
						customer_npc->getSprite().setTexture(customer_npc->getTextureIDLE());
						customer_npc->getSprite().setTextureRect(sf::IntRect({ 0,0 }, ENTITY_SIZE));
						auto recipe = items.getRecipeInfo(static_cast<int>(customer_npc->getOrder()));
						orderManager.addOrder(
							"order-" + std::to_string(static_cast<int>(customer_npc->getOrder())),
							{
								static_cast<unsigned int>(customer_npc->getOrder()),
								recipe->title,
								recipe->icon,
								recipe->customer_wait
							}
						); ordersDisplay.update();
					};
				};
			});
		};

		inline void setCustomerHandle(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			OrdersManager& orderManager,
			OrdersDisplay& ordersDisplay,
			Items& items,
			const std::string npc_id
		) {
			std::string npcName = "npc-customer-" + npc_id;
			if (!entityManager.getEntity(npcName)) return;

			auto customer = static_cast<NPC*>(entityManager.getEntity(npcName));
			auto movement_flags = std::make_shared<std::pair<bool, bool>>(false, false);
			customer->setHandler([this, movement_flags, &entityManager, &orderManager, &ordersDisplay, &items, npcName]() {
				auto player = (entityManager.getEntity("player")) ? static_cast<Player*>(entityManager.getEntity("player")) : nullptr;
				if (player) {
					auto npc = static_cast<NPC*>(entityManager.getEntity(npcName));
					if (static_cast<int>(player->getSelectedItem()) == static_cast<int>(npc->getOrder())) {
						player->setSelectedItem(0, items);
						orderManager.removeOrder("order-"+std::to_string(static_cast<int>(npc->getOrder())));
						ordersDisplay.update();
						npc->setEvent([this, npcName, movement_flags, &entityManager]() {
							auto npc = static_cast<NPC*>(entityManager.getEntity(npcName));
							float move_speed = static_cast<float>(-WALK_SPEED - (-WALK_SPEED * 0.5));

							if (!movement_flags->first) {
								if (npc->getSprite().getPosition() != customerMovement[1]) {
									npc->getSprite().move(0, -move_speed);
									npc->getAnimation().update(
										npc->getSprite(),
										npc->getTextureMoveVertical(),
										{ 0,0 }, { 16,16 },
										WALK_ANIM, 3, npc->getDelta()
									);
								} else movement_flags->first = true;
							}; 
							
							if (movement_flags->first && !movement_flags->second) {
								if (npc->getSprite().getPosition() != customerMovement[3]) {
									npc->getSprite().move(move_speed, 0);
									npc->getAnimation().update(
										npc->getSprite(),
										npc->getTextureMoveHorizontal(),
										{ 0,0 }, { 16,16 },
										WALK_ANIM, 3, npc->getDelta()
									);
								} else {
									movement_flags->second = true;
									hasCustomer = false;
									entityManager.removeEntity(npcName);
								};
							};

						});
					};
				};
			});
		};
};