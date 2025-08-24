#pragma once

#include "../../core/globals.hpp"
#include "../../core/resources/resources.hpp"
#include "../ui-manager.hpp"

class Pause {
	public:
		Pause() {};
		~Pause() {};
		Pause(Pause& const) = delete;
		Pause& operator=(Pause& const) = delete;
		inline static Pause& instance() {
			static Pause p;
			return p;
		};

		void setup();

	private:
		void initResources();
		void initElements();
		void initLayers();
		void createBackground();
		void createPanel();
		void createButtonContinue();
		void createButtonExit();

		Globals& globals = Globals::instance();
		ResourceManager& resourseManager = ResourceManager::instance();
		UIManager& uiManager = UIManager::instance();
};