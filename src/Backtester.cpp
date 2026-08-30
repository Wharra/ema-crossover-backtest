#include "../src/Backtester.hpp"
#include "../src/Strategy.hpp"

BacktestResult runBacktest(const std::vector<Bar>& bars,
                           const std::vector<double>& emaShort,
                           const std::vector<double>& emaLong,
                           const std::vector<double>& volumeAvg) {
    BacktestResult result;

    bool inPosition = false;
    double entryPrice = 0.0;

    for (size_t i = 0; i < bars.size(); ++i) {
        Signal signal = decideSignal(bars, emaShort, emaLong, volumeAvg, i);

        // we only act on Buy if we are not already in a position, and on Sell if we are in a position
        if (signal == Signal::Buy && !inPosition) {
            inPosition = true;
            entryPrice = bars[i].close;
        } else if (signal == Signal::Sell && inPosition) {
            double profit = bars[i].close - entryPrice;
            result.totalPnL += profit;
            if (profit > 0) {
                result.wins++;
            }
            result.numTrades++;
            inPosition = false;
        }

    }

    return result;
}