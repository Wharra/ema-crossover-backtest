#Basics
cmake_minimum_required(VERSION 3.16)          # need at least CMake 3.16
project(ema_crossover_backtest CXX)           # project name + language = C++

set(CMAKE_CXX_STANDARD 17)                    # compile with C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)           # C++17 is mandatory, no silent fallback

#My code
add_library(core src/Loader.cpp src/Processor.cpp src/Signal.cpp src/Strategy.cpp src/Backtester.cpp)              # build a library "core" from my .cpp files (business logic, no main)
target_include_directories(core PUBLIC src)   # headers live in src/ ; PUBLIC = whoever links to core inherits this

add_executable(app src/main.cpp)              # build the runnable program "app" (has main())
target_link_libraries(app PRIVATE core)       # app can use core's code

#Test framework
include(FetchContent)                         # enable downloading dependencies
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2                       # pin the version = reproducible builds
)
FetchContent_MakeAvailable(Catch2)            # download + build it now

#Tests
add_executable(tests tests/test_main.cpp)     # second program, separate from app
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain core)
                                              # Catch2WithMain = provides main() for tests
                                              # core = so tests can call my own code

enable_testing()                              # turn on ctest
add_test(NAME tests COMMAND tests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})