```markdown
# EMA Crossover Backtest

A backtesting engine in modern C++ for a moving-average crossover strategy.

## Strategy

Buy/sell signals are generated when a short exponential moving average (EMA 10)
crosses a long one (EMA 50). Signals are only kept when confirmed by volume
(daily volume above its 5-day average).

## Architecture

The pipeline is split into single-responsibility components, each independently testable:
```
```
Loader -> Processor -> Signal -> Strategy -> OrderSender
                                                |
                                           Backtester
```

| Component | Responsibility |
|---|---|
| `Bar` | Data type for one daily OHLCV candle |
| `Loader` | Reads market data (CSV, then Parquet/Yahoo) into `vector<Bar>` — no business logic |
| `Processor` | Computes indicators (EMA 10/50, 5-day volume average) — pure computation |
| `Signal` | Detects EMA crossovers, emits discrete buy/sell events |
| `Strategy` | Combines signal with the volume filter, produces the final decision |
| `OrderSender` | Abstract interface + mock implementation (FIX in production) |
| `Backtester` | Replays history, simulates trades, reports PnL and metrics |

## Build

Requires CMake (>= 3.16) and a C++17 compiler.

```bash
cmake -B build
cmake --build build
```

## Run

```bash
./build/app                                    # run the program
ctest --test-dir build --output-on-failure     # run the tests
./build/tests                                  # detailed test output
```

## Tech

- C++17
- CMake (`core` library + `app` and `tests` targets)
- Catch2 for unit testing
- Apache Arrow / Parquet for data storage (planned)

## Status

- [x] Project skeleton (CMake + Catch2)
- [x] `Bar` data type
- [x] CSV loader
- [x] Indicators (EMA, volume average)
- [x] Crossover signal detection
- [x] Strategy with volume filter
- [x] Order sender interface
- [ ] Backtest engine and metrics