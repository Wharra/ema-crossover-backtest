#include <catch2/catch_test_macros.hpp>
#include "../src/Bar.hpp"
#include "../src/Loader.hpp"
#include <catch2/catch_approx.hpp>  
#include "../src/Processor.hpp"
#include "../src/Signal.hpp"
#include "../src/Strategy.hpp"

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

TEST_CASE("volume average over a window") {
    auto bars = loadBarsFromCSV("data/sample.csv");
    auto vavg = computeVolumeAverage(bars, 2);

    REQUIRE(vavg.size() == 3);
    REQUIRE(vavg[0] == Catch::Approx(1000000));
    REQUIRE(vavg[1] == Catch::Approx(1100000));
    REQUIRE(vavg[2] == Catch::Approx(1050000));
}

TEST_CASE("strategy keeps volume-confirmed crosses, rejects weak ones") {
    // on fabrique 5 bars : seul le volume compte ici, le reste est bidon
    std::vector<Bar> bars = {
        {"d0", 0,0,0,0, 100},
        {"d1", 0,0,0,0, 100},
        {"d2", 0,0,0,0, 900},   // gros volume ce jour-là
        {"d3", 0,0,0,0, 100},
        {"d4", 0,0,0,0, 100},   // petit volume ce jour-là
    };

    // EMA : croisement UP au jour 2, croisement DOWN au jour 4
    std::vector<double> emaShort = {10, 10, 12, 12,  9};
    std::vector<double> emaLong  = {11, 11, 11, 11, 11};

    // moyenne de volume "de référence" = 200 partout (valeur posée à la main)
    std::vector<double> volumeAvg = {200, 200, 200, 200, 200};

    // jour 2 : cross = Buy ET volume 900 > 200 -> CONFIRMÉ -> Buy
    REQUIRE(decideSignal(bars, emaShort, emaLong, volumeAvg, 2) == Signal::Buy);

    // jour 4 : cross = Sell MAIS volume 100 < 200 -> REJETÉ -> None
    REQUIRE(decideSignal(bars, emaShort, emaLong, volumeAvg, 4) == Signal::None);

    // jour 3 : pas de cross du tout -> None
    REQUIRE(decideSignal(bars, emaShort, emaLong, volumeAvg, 3) == Signal::None);
}