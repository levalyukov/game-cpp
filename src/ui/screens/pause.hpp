#pragma once

#include "screen.hpp"
#include "../../core/globals.hpp"
#include "../../core/resources/resources.hpp"
#include "../ui-manager.hpp"

#include <string>

class Pause : public Screen {
	public:
		Pause(
			UIManager& ui_manager,
			ResourceManager& resourse_manager,
			Globals& global_manager
		) : uiManager(ui_manager),
			resourseManager(resourse_manager),
			globals(global_manager) {};

		void setup() override;

	private:
		Globals& globals;
		ResourceManager& resourseManager;
		UIManager& uiManager;

		void initResources();
		void initElements();
		void initLayers();

		void initParameters();
		void initBackground();
		void initPanel();
		void initButtonContinue();
		void initButtonExit();
		void initLabels();
};