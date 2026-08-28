#include "../src/Strategy.hpp"
#include "../src/Signal.hpp"   // we call detectCross here

Signal decideSignal(const std::vector<Bar>& bars,
                    const std::vector<double>& emaShort,
                    const std::vector<double>& emaLong,
                    const std::vector<double>& volumeAvg,
                    size_t i) {

    // step 1: get the raw cross signal at day i (Buy / Sell / None)
    // -> call detectCross(...) and store it in a Signal variable named "cross"
    Signal cross = detectCross(emaShort, emaLong, i);

    // step 2: if there is no cross, there is nothing to confirm
    // -> if cross is None, return None
    if (cross == Signal::None) {
        return Signal::None;
    }

    // step 3: volume filter -> keep the signal only if today's volume
    //         is above its average (cross confirmed by real activity)
    // -> if bars[i].volume > volumeAvg[i]  return cross
    // -> otherwise                          return None
    if (bars[i].volume > volumeAvg[i]) {
        return cross;
    } else {
        return Signal::None;
    }
}