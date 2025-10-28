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

class Characters {
	public:
		std::vector<sf::Vector2f> passerbyMovement = {
			sf::Vector2f(0,8 * 64), sf::Vector2f(0,8 * 64 + 48), sf::Vector2f(0,8 * 64 + 32), sf::Vector2f(0,8 * 64 -32),
			sf::Vector2f(25 * 64,8 * 64), sf::Vector2f(25 * 64,8 * 64 + 48), sf::Vector2f(25 * 64,8 * 64 + 32), sf::Vector2f(0,8 * 64 -32),
		};

		std::vector<sf::Vector2f> customerMovement = {
			sf::Vector2f(25 * 64,8 * 64), sf::Vector2f(12 * 64,8 * 64), sf::Vector2f(12 * 64,7 * 64) // Movement to the restaurant
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
			std::string new_customer_id = generetingNewCustomerID(entityManager);
			initNPCResources(resourceManager, new_customer_id);
			spawnCustomer(resourceManager, entityManager, new_customer_id);
			setCustomerEvent(resourceManager, entityManager, orderManager, eventManager, ordersDisplay, items, new_customer_id);
		};

	private:
		Utils utils;
		const int DELETE_PASSERBY = 1000;

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

		inline unsigned int getOrder(Items& items) {
			std::random_device rd; 
			std::mt19937 rand(rd());
			std::uniform_int_distribution<int> dist(1, items.getRecipesSize());
			return dist(rd);
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
			passerby->setEvent(
				[this, npcName, passerby, direction, vector, &entityManager]() {
					auto npc = static_cast<NPC*>(passerby);
					auto player = static_cast<Player*>(entityManager.getEntity("player"));
					static float time = 0.f;
					npc->getSprite().move({ static_cast<float>(direction - (direction * 0.5)),0 });
					npc->getAnimation().update(npc->getSprite(), npc->getTextureMoveHorizontal(), vector, {16,16}, WALK_ANIM, 3, npc->getDelta());
					if (entityManager.getDistance(player->getSprite(), npc->getSprite()) > DELETE_PASSERBY) {
						entityManager.removeEntity(npcName);
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

			auto customer = entityManager.getEntity(npcName);
			auto player = static_cast<Player*>(entityManager.getEntity("player"));
			float direction = getDirection();
			sf::Vector2i vector = getVector(direction);
			static_cast<NPC*>(customer)->getSprite().setPosition(customerMovement[0]);
			customer->setEvent(
				[this, npcName, npc_id, &entityManager, &eventManager, &orderManager, &ordersDisplay, &items]() {
					auto customer_npc = static_cast<NPC*>(entityManager.getEntity(npcName));
					static bool move_flag_1 = false;
					static bool move_flag_2 = false;

					if (!move_flag_1) {
						if (customer_npc->getSprite().getPosition() != customerMovement[1]) {
							customer_npc->getSprite().move(static_cast<float>(-WALK_SPEED - (-WALK_SPEED * 0.5)), 0);
							customer_npc->getAnimation().update(
								customer_npc->getSprite(),
								customer_npc->getTextureMoveHorizontal(),
								{ 0,0 }, { 16,16 },
								WALK_ANIM, 3, customer_npc->getDelta()
							);
						} else move_flag_1 = true;
					};

					if (move_flag_1 && !move_flag_2) {
						if (customer_npc->getSprite().getPosition() != customerMovement[2]) {
							customer_npc->getSprite().move(0, static_cast<float>(-WALK_SPEED - (-WALK_SPEED * 0.5)));
							customer_npc->getAnimation().update(
								customer_npc->getSprite(),
								customer_npc->getTextureMoveVertical(),
								{ 0,16 }, { 16,16 },
								WALK_ANIM, 3, customer_npc->getDelta()
							);
						} else {
							move_flag_2 = true;
							customer_npc->getSprite().setTexture(customer_npc->getTextureIDLE());
							customer_npc->getSprite().setTextureRect(sf::IntRect({ 0,0 }, ENTITY_SIZE));
							static unsigned int customer_order = getOrder(items);
							eventManager.addEvent(
								"order-" + npc_id, { [&orderManager, &ordersDisplay, &items]() {
									std::cout << "The customer has placed an order: " + std::to_string(customer_order) << std::endl;
									auto recipe = items.getRecipeInfo(customer_order);
									orderManager.addOrder("order-" + std::to_string(customer_order), { customer_order, recipe->title, recipe->cook_time, recipe->icon_path, recipe->customer_wait });
									ordersDisplay.update();
								}, 1.f }
							);
						};
					};

				}
			);
		};
};