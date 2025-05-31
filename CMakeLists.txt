cmake_minimum_required(VERSION 3.14)
project(TP3SGN)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

find_package(pybind11 CONFIG REQUIRED)

find_package(matplotplusplus QUIET)
if (NOT matplotplusplus_FOUND)
    message(STATUS "Matplotplusplus not found system-wide; fetching via FetchContent")
    include(FetchContent)
    set(FETCHCONTENT_QUIET OFF)
    FetchContent_Declare(
    matplotplusplus
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
    )
    FetchContent_MakeAvailable(matplotplusplus)
endif()

find_package(Threads REQUIRED)

pybind11_add_module(signal_lib signal_lib.cpp)
target_link_libraries(signal_lib PRIVATE matplot Threads::Threads)

add_executable(signal_test_cpp test.cpp)
target_link_libraries(signal_test_cpp PRIVATE matplot Threads::Threads)