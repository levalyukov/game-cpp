#pragma once

#include "../../core/resources/resources.hpp"
#include "../../core/states.hpp"
#include "../ui-manager.hpp"

class Pause {
	public:
		Pause();

	protected:
		void initResources();
		void initElements();
		void createBackground();
		void createButtonContinue();
		//void createButtonSettings();
		void createButtonExit();
		ResourceManager& resourseManager = ResourceManager::instance();
		UIManager& uiManager = UIManager::instance();
		GameState& gameState = GameState::instance();
};