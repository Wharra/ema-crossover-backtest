/*
cmake --build build                           # 1 compile
./build/app                                   # 2 lance le programme
ctest --test-dir build --output-on-failure    # 3 lance les tests
*/

#include <iostream>
#include "../src/Loader.hpp"
#include "../src/Processor.hpp"
#include "../src/Signal.hpp"
#include "../src/Strategy.hpp"
#include "../src/ConsoleOrderSender.hpp"

int main() {
    // on charge les données
    std::vector<Bar> bars = loadBarsFromCSV("data/aapl.csv");

    // on calcule les indicateurs
    std::vector<double> emaShort  = computeEMA(bars, 10);
    std::vector<double> emaLong   = computeEMA(bars, 50);
    std::vector<double> volumeAvg = computeVolumeAverage(bars, 5);

    // appareil qui exécute les ordres
    ConsoleOrderSender sender;

    // boucle sur chaque jour
    for (size_t i = 0; i < bars.size(); ++i) {
        Signal signal = decideSignal(bars, emaShort, emaLong, volumeAvg, i);
        if (signal != Signal::None) {
            sender.send(signal, bars[i].close);
        }
    }

    return 0;
}