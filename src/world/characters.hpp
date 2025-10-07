#pragma once


#include "../core/animations/animations.hpp"
#include "../core/resources/resources.hpp"
#include "../mechanics/inventory-manager.hpp"
#include "../mechanics/economy-manager.hpp"
#include "../entities/entity-manager.hpp"
#include "../entities/entities/player.hpp"
#include "../entities/entities/npc.hpp"
#include "../ui/screens/inventory.hpp"
#include "../ui/screens/hud.hpp"
#include "../core/utils.hpp"

class Characters {
	public:
		//std::vector<sf::Vector2i> passerbyPositions = {
		//	sf::Vector2i(0,0), sf::Vector2i(0,0)
		//};

		inline void spawn(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			InventoryManager& inventoryManager,
			EconomyManager& economyManager,
			Inventory& inventoryUI,
			HUD& hud
		) {
			player(resourceManager, entityManager);
		};

		inline void passerby(
			ResourceManager& resourceManager,
			EntityManager& entityManager
		) {
			std::string new_npc_id = generetingNewPasserbyID(entityManager);
			initPasserbyResources(resourceManager, new_npc_id);
			spawnPasserby(resourceManager, entityManager, new_npc_id);
			setPasserbyEvent(resourceManager, entityManager, new_npc_id);
		};

		inline void customer(
			ResourceManager& resourceManager,
			EntityManager& entityManager
		) {
			std::cout << "Spawn customer;\n";
		};

	private:
		Utils utils;
		AnimationManager anim;

		const int DELETE_PASSERBY = 700;

		/////////////////////////////////////////////////////////

		inline float getDirection() {
			if (utils.rangeRandom(0, 1) == 0) return -WALK_SPEED;
			else return WALK_SPEED;
		};

		inline sf::Vector2i getVector(const float direction) {
			if (direction < 0) return sf::Vector2i(0, 0);
			else return sf::Vector2i(0, 16);
		};


		inline std::string generetingNewPasserbyID(EntityManager& entityManager) {
			unsigned __int16 id = 0;
			unsigned __int16 attempts = 0;
			while (attempts < 10) {
				id = utils.rangeRandom(0, 10);
				if (entityManager.getEntity("npc-" + std::to_string(static_cast<int>(id)))) attempts++;
				else break;
			}; return std::to_string(static_cast<int>(id));
		};

		/////////////////////////////////////////////////////////

		inline void player(ResourceManager& resourceManager, EntityManager& entityManager) const {
			resourceManager.loadTexture("character-idle", "../../../assets/textures/entity/player/character_idle.png");
			resourceManager.loadTexture("character-walk-horizontal", "../../../assets/textures/entity/player/character_walk_horizontal.png");
			resourceManager.loadTexture("character-walk-vertical", "../../../assets/textures/entity/player/character_walk_vertical.png");
			resourceManager.loadTexture("character-shadow", "../../../assets/textures/entity/player/character_shadow.png");
			
			entityManager.addEntity(
				"player",
				std::make_unique<Player>(
					resourceManager.getTexture("character-idle"),
					resourceManager.getTexture("character-walk-horizontal"),
					resourceManager.getTexture("character-walk-vertical"),
					resourceManager.getTexture("character-shadow")
			));
		};

		inline void initPasserbyResources(
			ResourceManager& resourceManager,
			const std::string npc_id
		) {
			if (resourceManager.getTexture("npc-" + npc_id + "-idle")) return;
			if (resourceManager.getTexture("npc-" + npc_id + "-walk-horizontal")) return;
			if (resourceManager.getTexture("npc-" + npc_id + "-walk-vertical")) return;
			if (resourceManager.getTexture("npc-" + npc_id + "-shadow")) return;

			resourceManager.loadTexture("npc-" + npc_id + "-idle", "../../../assets/textures/entity/npc/npc_idle.png");
			resourceManager.loadTexture("npc-" + npc_id + "-walk-horizontal", "../../../assets/textures/entity/npc/npc_movement_horizontal.png");
			resourceManager.loadTexture("npc-" + npc_id + "-walk-vertical", "../../../assets/textures/entity/npc/npc_movement_vertical.png");
			resourceManager.loadTexture("npc-" + npc_id + "-shadow", "../../../assets/textures/entity/player/character_shadow.png");
		};
		
		inline void spawnPasserby(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			const std::string npc_id
		) {
			if (!resourceManager.getTexture("npc-" + npc_id + "-idle")) return;
			if (!resourceManager.getTexture("npc-" + npc_id + "-walk-horizontal")) return;
			if (!resourceManager.getTexture("npc-" + npc_id + "-walk-vertical")) return;
			if (!resourceManager.getTexture("npc-" + npc_id + "-shadow")) return;

			entityManager.addEntity(
				"npc-" + npc_id,
				std::make_unique<NPC>(
					resourceManager.getTexture("npc-" + npc_id + "-idle"),
					resourceManager.getTexture("npc-" + npc_id + "-walk-horizontal"),
					resourceManager.getTexture("npc-" + npc_id + "-walk-vertical"),
					resourceManager.getTexture("npc-" + npc_id + "-shadow")
			));
		};

		inline void setPasserbyEvent(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			const std::string npc_id
		) {
			std::string npcName = "npc-" + npc_id;
			auto passerby = entityManager.getEntity(npcName);

			float direction = getDirection();
			sf::Vector2i currentVector = getVector(direction);
			sf::Texture* passerbyTexture = resourceManager.getTexture("npc-" + npc_id + "-walk-horizontal");

			passerby->setEvent(
				[this, npcName, passerby, direction, passerbyTexture, currentVector, &entityManager]() {
				auto npc = static_cast<NPC*>(passerby);
				auto player = static_cast<Player*>(entityManager.getEntity("player"));

				float time = 0.f;
				npc->getSprite().move({ static_cast<float>(direction - (direction * 0.5)),0 });
				anim.update(npc->getSprite(), *passerbyTexture, currentVector, { 16,16 }, WALK_ANIM, 3, npc->getDelta());

				if (entityManager.getDistance(player->getSprite(), npc->getSprite()) > DELETE_PASSERBY) {
					entityManager.removeEntity(npcName);
				};
			});
		};
};