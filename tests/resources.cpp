#include <catch2/catch_all.hpp>
#include "../src/core/resources/resources.hpp"

std::unique_ptr<ResourceManager> resourceManager = std::make_unique<ResourceManager>();

/* Fonts */

TEST_CASE("Uploading a font") {
	resourceManager->loadFont("arial", "../../../assets/fonts/arial.ttf");
	CHECK(resourceManager->getFont("arial") != nullptr);
	resourceManager->removeFont("arial");
}

TEST_CASE("Getting a deleted font") {
	resourceManager->loadFont("nunito", "../../../assets/fonts/nunito.ttf");
	resourceManager->removeFont("nunito");
	CHECK(resourceManager->getFont("nunito") == nullptr);
}

TEST_CASE("Getting an unknown font") {
	CHECK(resourceManager->getFont("unknown-font") == nullptr);
}

TEST_CASE("Getting a font with a random case") {
	resourceManager->loadFont("test-font", "../../../assets/fonts/nunito.ttf");
	CHECK(resourceManager->getFont("TEST-font") != nullptr);
	resourceManager->removeFont("test-FONT");
}

/* Textures */

TEST_CASE("Adding texture") {
	resourceManager->loadTexture("test-texture", "../../../assets/icon.png");
	CHECK(resourceManager->getTexture("test-texture") != nullptr);
	resourceManager->removeTexture("test-texture");
}

TEST_CASE("Getting a deleted texture") {
	resourceManager->loadTexture("test-deleted-icon", "../../../assets/icon.png");
	resourceManager->removeTexture("test-deleted-icon");
	CHECK(resourceManager->getTexture("test-deleted-icon") == nullptr);
}

TEST_CASE("Getting an unknown texture") {
	CHECK(resourceManager->getTexture("test-deleted-icon") == nullptr);
}

TEST_CASE("Getting a texture with a random case") {
	resourceManager->loadTexture("test-icon", "../../../assets/icon.png");
	CHECK(resourceManager->getTexture("TEST-iCon") != nullptr);
	resourceManager->removeTexture("tEsT-ICon");
}