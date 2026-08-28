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

// simple moving average of volume over a given window
std::vector<double> computeVolumeAverage(const std::vector<Bar>& bars, int window) {
    std::vector<double> result;

    if (bars.empty() || window <= 0) {
        return result; // same defensive guard as the EMA
    }

    for (size_t i = 0; i < bars.size(); ++i) {
        //window start, clamped to 0 so we never underflow on the first days
        size_t start = (i + 1 >= (size_t)window) ? (i + 1 - window) : 0;

        double sum = 0.0;
        for (size_t j = start; j <= i; ++j) {
            sum += bars[j].volume;  //add up the volumes in the window
        }

        result.push_back(sum / (i - start + 1)); //divide by the real number of days
    }

    return result;
}