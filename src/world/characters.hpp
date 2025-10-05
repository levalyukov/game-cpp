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
		inline void spawn(
			ResourceManager& resourceManager,
			EntityManager& entityManager,
			InventoryManager& inventoryManager,
			EconomyManager& economyManager,
			Inventory& inventoryUI,
			HUD& hud
		) {
			player(resourceManager, entityManager);
			passerby(resourceManager, entityManager);
		};

	private:
		AnimationManager anim;
		const int DELETE_PASSERBY = 500;

		inline float getDirection() {
			Utils utils;
			if (utils.rangeRandom(0, 1) == 0) return -WALK_SPEED;
			else return WALK_SPEED;
		};

		inline sf::Vector2i getVector(const float direction) {
			if (direction < 0) return sf::Vector2i(0, 0);
			else return sf::Vector2i(0, 16);
		};

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
				)
			);
		};

		inline void passerby(
			ResourceManager& resourceManager, 
			EntityManager& entityManager
		) {
			resourceManager.loadTexture("npc-idle", "../../../assets/textures/entity/npc/npc_idle.png");
			resourceManager.loadTexture("npc-walk-horizontal", "../../../assets/textures/entity/npc/npc_movement_horizontal.png");
			resourceManager.loadTexture("npc-walk-vertical", "../../../assets/textures/entity/npc/npc_movement_vertical.png");
			resourceManager.loadTexture("npc-shadow", "../../../assets/textures/entity/player/character_shadow.png");
			entityManager.addEntity(
				"npcTest",
				std::make_unique<NPC>(
					resourceManager.getTexture("npc-idle"),
					resourceManager.getTexture("npc-walk-horizontal"),
					resourceManager.getTexture("npc-walk-vertical"),
					resourceManager.getTexture("npc-shadow")
				)
			);

			entityManager.getEntity("npcTest")->setEvent([&]() {
				auto player = static_cast<Player*>(entityManager.getEntity("player"));
				auto npc = static_cast<NPC*>(entityManager.getEntity("npcTest"));

				static float time = 0.f;
				static float direction = getDirection();
				static sf::Vector2i currentVector = getVector(direction);
				npc->getSprite().move({ static_cast<float>(direction - (direction * 0.5)),0 });

				anim.update(
					npc->getSprite(), 
					*resourceManager.getTexture("npc-walk-horizontal"), 
					currentVector, { 16,16 }, WALK_ANIM, 3, npc->getDelta()
				);

				if (entityManager.getDistance(player->getSprite(), npc->getSprite()) > DELETE_PASSERBY) {
					entityManager.removeEntity("npcTest");
				};
			});
		};
};