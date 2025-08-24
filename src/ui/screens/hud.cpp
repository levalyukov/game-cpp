#include "hud.hpp"

void HUD::setup() {
	initResources();
	initElements();
	initLayers();
}

void HUD::initResources() {
	resourceManager.loadTexture("hud-recipe-button", "../../../assets/textures/ui/hud/recipe-button.png");
}

void HUD::initElements() {
	uiManager.addElement("hud-button", uiManager.gui.createButton(resourceManager.getTexture("hud-recipe-button"), { 32,32 }));
}

void HUD::initLayers() {
	
}