#pragma once
#include <vector>
#include "Bar.hpp"

//we compute the EMA of closing prices for a given period
std::vector<double> computeEMA(const std::vector<Bar>& bars, int period);

