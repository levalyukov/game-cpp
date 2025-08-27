#pragma once

#include "../entities/entity-manager.hpp"
#include "../core/resources/resources.hpp"
#include "../entities/entities/player.hpp"
#include "../entities/entities/npc.hpp"

class Characters {
	public:
		inline void spawn(ResourceManager& resourceManager, EntityManager& entityManager) {
			player(resourceManager, entityManager);
			npcs(resourceManager, entityManager);
		}

	private:
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

		inline void npcs(ResourceManager& resourceManager, EntityManager& entityManager) const {
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
		};
};