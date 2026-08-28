#include <catch2/catch_test_macros.hpp>
#include "../src/Bar.hpp"
#include "../src/Loader.hpp"
#include <catch2/catch_approx.hpp>  
#include "../src/Processor.hpp"

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

#include "../src/Processor.hpp"   // en haut avec les autres includes

TEST_CASE("EMA is computed correctly") {
    auto bars = loadBarsFromCSV("data/sample.csv");
    auto ema = computeEMA(bars, 2);

    REQUIRE(ema.size() == 3);
    REQUIRE(ema[0] == Catch::Approx(101.0));    // amorce = 1er close
    REQUIRE(ema[1] == Catch::Approx(102.0));
    REQUIRE(ema[2] == Catch::Approx(101.0));
}
