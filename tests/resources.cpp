#include <catch2/catch_all.hpp>

#include "../src/core/resources/resources.hpp"

std::unique_ptr<ResourceManager> resourceManager = std::make_unique<ResourceManager>();

// Fonts

TEST_CASE("Uploading a font") {
	resourceManager->loadFont("arial", "../../../assets/fonts/arial.ttf");
	sf::Font* target_font = resourceManager->getFont("arial");
	CHECK(target_font != nullptr);
}

TEST_CASE("Uploading a deleted font") {
	resourceManager->loadFont("nunito", "../../../assets/fonts/nunito.ttf");
	resourceManager->removeFont("nunito");
	sf::Font* target_font = resourceManager->getFont("nunito");
	CHECK(target_font == nullptr);
}