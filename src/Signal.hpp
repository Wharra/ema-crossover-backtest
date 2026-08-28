#pragma once
#include <vector>

enum class Signal {
    None,
    Buy,
    Sell
};

Signal detectCross(const std::vector<double>& emaShort,
                   const std::vector<double>& emaLong,
                   size_t i);