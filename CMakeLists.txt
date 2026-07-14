cmake_minimum_required(VERSION 3.16)
project(ema_crossover_backtest CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app src/main.cpp)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/test_main.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

enable_testing()
add_test(NAME unit_tests COMMAND tests)
