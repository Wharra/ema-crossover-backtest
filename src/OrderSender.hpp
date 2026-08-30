#pragma once
#include "Signal.hpp"

// the "socket" : any order sender must know how to send an order
class OrderSender {
public:
    virtual ~OrderSender() = default;                     // (technical detail, ignore for now)
    virtual void send(Signal signal, double price) = 0;   // the shape of the plug, empty
};