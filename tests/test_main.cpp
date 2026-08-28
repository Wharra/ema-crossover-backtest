#include <catch2/catch_test_macros.hpp>
#include "../src/Bar.hpp"
#include "../src/Loader.hpp"
#include <catch2/catch_approx.hpp>  
#include "../src/Processor.hpp"
#include "../src/Signal.hpp"

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

TEST_CASE("detectCross finds golden and death crosses") {
    std::vector<double> emaShort = {10, 10, 12, 12,  9};
    std::vector<double> emaLong  = {11, 11, 11, 11, 11};

    REQUIRE(detectCross(emaShort, emaLong, 0) == Signal::None);  // no previous day
    REQUIRE(detectCross(emaShort, emaLong, 1) == Signal::None);  // still below
    REQUIRE(detectCross(emaShort, emaLong, 2) == Signal::Buy);   // crosses up
    REQUIRE(detectCross(emaShort, emaLong, 3) == Signal::None);  // stays above
    REQUIRE(detectCross(emaShort, emaLong, 4) == Signal::Sell);  // crosses down
}