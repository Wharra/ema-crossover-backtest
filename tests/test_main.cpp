#include <catch2/catch_test_macros.hpp>
#include "../src/Bar.hpp"

TEST_CASE("skeleton sanity check") {
    REQUIRE(1 + 1 == 2);
}

TEST_CASE("Bar stores its field") {
    Bar b; // bar b is 
    b.close = 100.5;
    REQUIRE(b.close == 100.5);
}