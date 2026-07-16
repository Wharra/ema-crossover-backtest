/*
cmake --build build                           # 1 compile
./build/app                                   # 2 lance le programme
ctest --test-dir build --output-on-failure    # 3 lance les tests
*/


#include <iostream>
#include "../src/Bar.hpp"

int main() {
    std::cout << "EMA crossover backtester - Salut c'est Armand!\n";
    return 0;
}