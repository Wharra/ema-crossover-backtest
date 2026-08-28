#include "../src/Signal.hpp"

Signal detectCross(const std::vector<double>& emaShort,
                   const std::vector<double>& emaLong,
                   size_t i) {
    if (i == 0) return Signal::None;   // no previous day -> no cross possible

    if (emaShort[i-1] <= emaLong[i-1] && emaShort[i] > emaLong[i])
        return Signal::Buy;
    else if (emaShort[i-1] >= emaLong[i-1] && emaShort[i] < emaLong[i])
        return Signal::Sell;
    else
        return Signal::None;
}