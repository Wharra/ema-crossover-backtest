#pragma once // to prevent for multiple inclusions 
#include <string>

// let's define a Bar (6infos per days)
// 1. date, 2. open, 3. high, 4. low, 5. close, 6. volume

struct Bar {
    std::string date;
    double open;
    double high;
    double low;
    double close;
    double volume;
};