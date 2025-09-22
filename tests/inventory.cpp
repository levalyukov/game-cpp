#include <catch2/catch_all.hpp>
#include "../src/mechanics/inventory-manager.hpp"

TEST_CASE("Add item in container") {
	InventoryManager inv;
	inv.addItem("bread", { "Bread" });
	CHECK(inv.getItem("bread") != nullptr);
};

TEST_CASE("Add new count for item") {
	InventoryManager inv;
	inv.addItem("bread", { "Bread" });
	inv.addItemValue("bread", 25);
	CHECK(inv.getItem("bread")->value == 26);
}

TEST_CASE("Subtract the value of item") {
	InventoryManager inv;
	inv.addItem("bread", { "Bread" });
	inv.addItemValue("bread", 25);
	inv.subtractItemValue("bread", 6);
	CHECK(inv.getItem("bread")->value == 20);
}

TEST_CASE("Set the value of item") {
	InventoryManager inv;
	inv.addItem("bread", { "Bread" });
	inv.setItemValue("bread", 5);
	CHECK(inv.getItem("bread")->value == 5);
}