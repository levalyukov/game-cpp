#pragma once

#include "../../core/resources/resources.hpp"
#include "../../core/states.hpp"
#include "../ui-manager.hpp"

class Pause {
	public:
		Pause();

		void createPauseUI();

	protected:
		void initResources();
		void initElements();
		ResourceManager& resourseManager = ResourceManager::instance();
		UIManager& uiManager = UIManager::instance();
		GameState& gameState = GameState::instance();
};