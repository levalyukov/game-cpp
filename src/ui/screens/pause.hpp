#pragma once

#include "../../core/globals.hpp"
#include "../../core/resources/resources.hpp"
#include "../ui-manager.hpp"

class Pause {
	public:
		Pause(
			UIManager& ui_manager,
			ResourceManager& resourse_manager
		) : uiManager(ui_manager),
			resourseManager(resourse_manager) {};

		void setup();

	private:
		Globals& globals = Globals::instance();
		ResourceManager& resourseManager;
		UIManager& uiManager;

		void initResources();
		void initElements();
		void initLayers();
		void createBackground();
		void createPanel();
		void createButtonContinue();
		void createButtonExit();
};