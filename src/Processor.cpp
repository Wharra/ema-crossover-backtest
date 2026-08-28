#include "../src/Processor.hpp"

std::vector<double> computeEMA(const std::vector<Bar>& bars, int period) {
    std::vector<double> ema;
    
    if (bars.empty() || period <= 0) {
        return ema; // Return empty vector if input is invalid
    }

    //calculer k
    double k = 2.0 / (period + 1);
    ema.push_back(bars[0].close); // We initialize EMA with the first closing price
    
    for (size_t i = 1; i < bars.size(); ++i) {
        ema.push_back(k * bars[i].close + (1 - k) * ema[i - 1]);
    }

    return ema;
}