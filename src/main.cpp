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
#include "../src/Backtester.hpp"

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

    // run the backtest
    BacktestResult result = runBacktest(bars, emaShort, emaLong, volumeAvg);

    std::cout << "\n===== BACKTEST RESULTS =====\n";
    std::cout << "Total PnL : " << result.totalPnL << "\n";
    std::cout << "Trades    : " << result.numTrades << "\n";
    std::cout << "Wins      : " << result.wins << "\n";

    if (result.numTrades > 0) {
        double winRate = 100.0 * result.wins / result.numTrades;
        std::cout << "Win rate  : " << winRate << " %\n";
    }

    return 0;   // <-- tout en bas : c'est la dernière chose qui s'exécute
}