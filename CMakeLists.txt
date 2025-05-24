cmake_minimum_required(VERSION 3.14)
project(TP3SGN)

set(CMAKE_CXX_STANDARD 17)

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

set(SOURCES
    main.cpp
)

add_executable(sgn_main ${SOURCES})
target_link_libraries(sgn_main PRIVATE matplot)