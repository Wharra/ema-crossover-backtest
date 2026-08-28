#pragma once
#include <vector>
#include "Bar.hpp"
#include "Signal.hpp"

// decide the final action at day i: cross signal confirmed by volume
Signal decideSignal(const std::vector<Bar>& bars,
                    const std::vector<double>& emaShort,
                    const std::vector<double>& emaLong,
                    const std::vector<double>& volumeAvg,
                    size_t i);