#include <catch2/catch_all.hpp>
#include "../src/mechanics/warehouse-manager.hpp"

TEST_CASE("Adding item in storage") {
	WarehouseManager wm;
	wm.addItem("test", { "test" });
	CHECK(wm.getItem("test") != nullptr);
};