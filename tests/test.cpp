#include <catch2/catch_all.hpp>

unsigned int plus(int value) {
	return value + 5;
}

TEST_CASE("First test") {
	REQUIRE(plus(5) == 10);
}