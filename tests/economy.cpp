#include <catch2/catch_all.hpp>

#include "../src/economy/economy.hpp"

Economy& economyManager = Economy::Instance();

/*! checking addMoney() func */
TEST_CASE("Adding positive value", "[economy]") {
	economyManager.setMoney(0); // Reset
	economyManager.addMoney(100);
	CHECK(economyManager.getMoney() == 100);
}

TEST_CASE("Adding negative value", "[economy]") {
	economyManager.setMoney(0); // Reset
	economyManager.addMoney(-100);
	CHECK(economyManager.getMoney() == 0);
}

TEST_CASE("Adding positive+negative value", "[economy]") {
	economyManager.setMoney(0); // Reset
	economyManager.addMoney(6010);
	economyManager.addMoney(-100);
	CHECK(economyManager.getMoney() == 6010);
}

/*! checking removeMoney() func */
TEST_CASE("Removing positive value", "[economy]") {
	economyManager.setMoney(0); // Reset
	economyManager.addMoney(100);
	economyManager.removeMoney(105);
	CHECK(economyManager.getMoney() == 0);
}

TEST_CASE("Removing negative value", "[economy]") {
	economyManager.setMoney(0); // Reset
	economyManager.addMoney(100);
	economyManager.removeMoney(-105);
	CHECK(economyManager.getMoney() == 100);
}

TEST_CASE("Removing negative+negative value", "[economy]") {
	economyManager.setMoney(0); // Reset
	economyManager.addMoney(-100);
	economyManager.removeMoney(-105);
	CHECK(economyManager.getMoney() == 0);
}

/*! checking setMoney() func */
TEST_CASE("Setting positive value", "[economy]") {
	economyManager.setMoney(0); // Reset
	economyManager.setMoney(100);
	CHECK(economyManager.getMoney() == 100);
}

TEST_CASE("Setting negative value", "[economy]") {
	economyManager.setMoney(0); // Reset
	economyManager.setMoney(-100);
	CHECK(economyManager.getMoney() == 0);
}
