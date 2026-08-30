#pragma once
#include <vector>
#include "Bar.hpp"
#include "Signal.hpp"

// results of a backtest run
struct BacktestResult {
    double totalPnL = 0.0;
    int numTrades = 0;       //closed trades (buy->sell)
    int wins = 0;            //number of profitable trades
};

//run the strategy over the data and measure performance
BacktestResult runBacktest(const std::vector<Bar>& bars,
                           const std::vector<double>& emaShort,
                           const std::vector<double>& emaLong,
                           const std::vector<double>& volumeAvg);