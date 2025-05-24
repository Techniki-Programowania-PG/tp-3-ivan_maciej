cmake_minimum_required(VERSION 3.14)
project(TP3SGN)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/matplotplusplus)

set(SOURCES
    main.cpp
)

add_executable(sgn_main ${SOURCES})
target_link_libraries(sgn_main PRIVATE matplot)