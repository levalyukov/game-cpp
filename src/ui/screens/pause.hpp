#pragma once

#include "../../core/globals.hpp"
#include "../../core/resources/resources.hpp"
#include "../ui-manager.hpp"

class Pause {
	public:
		Pause();

	protected:
		void initResources();
		void initElements();
		void createBackground();
		void createButtonContinue();
		void createButtonExit();
		ResourceManager& resourseManager = ResourceManager::instance();
		UIManager& uiManager = UIManager::instance();
};