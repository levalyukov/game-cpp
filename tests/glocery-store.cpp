#include <catch2/catch_all.hpp>
#include "../src/mechanics/glocery-shop-manager.hpp"

TEST_CASE("Adding product in the shop") {
	GloceryShopManager gsm; gsm.shop.clear();
	gsm.addProduct("milk", { "Milk", 100, 10 });
	CHECK(gsm.getProduct("milk") != nullptr);
};

TEST_CASE("Getting product value in the shop") {
	GloceryShopManager gsm; gsm.shop.clear();
	gsm.addProduct("milk", { "Milk", 100, 10 });
	CHECK(gsm.getProduct("milk")->value == 10);
};

TEST_CASE("Removing product in the shop") {
	GloceryShopManager gsm; gsm.shop.clear();
	gsm.addProduct("milk", { "Milk", 100, 10 });
	gsm.removeProduct("milk");
	CHECK(gsm.getProduct("milk") == nullptr);
};

TEST_CASE("Getting a unknown product in the shop") {
	GloceryShopManager gsm; gsm.shop.clear();
	CHECK(gsm.getProduct("unknown") == nullptr);
};

TEST_CASE("Getting a product with random case in the shop") {
	GloceryShopManager gsm; gsm.shop.clear();
	gsm.addProduct("MiLk", { "Milk", 100, 10 });
	CHECK(gsm.getProduct("mIlK") != nullptr);
};