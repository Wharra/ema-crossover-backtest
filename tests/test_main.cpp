#include <catch2/catch_test_macros.hpp>
#include "../src/Bar.hpp"
#include "../src/Loader.hpp"
#include <catch2/catch_approx.hpp>  

TEST_CASE("skeleton sanity check") {
    REQUIRE(1 + 1 == 2);
}

TEST_CASE("Bar stores its field") {
    Bar b; // bar b is 
    b.close = 100.5;
    REQUIRE(b.close == 100.5);
}

TEST_CASE("Loader reads a CSV into Bars") {
    auto bars = loadBarsFromCSV("data/sample.csv");

    REQUIRE(bars.size() == 3);
    REQUIRE(bars[0].date == "2024-01-02");
    REQUIRE(bars[2].close == Catch::Approx(100.5));
}

