#pragma once
#include "../src/OrderSender.hpp"
#include <iostream>

// an "appliance" that plugs into the socket : it just prints the order
class ConsoleOrderSender : public OrderSender {
public:
    void send(Signal signal, double price) override {
        if (signal == Signal::Buy) {
            std::cout << "BUY at " << price << "\n";
        } else if (signal == Signal::Sell) {
            std::cout << "SELL at " << price << "\n";
        }
        // None : on n'envoie rien
    }
};