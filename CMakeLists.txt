cmake_minimum_required(VERSION 3.10)

project(graph_stuff)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(rapidcsv)

add_executable(graphs src/main.cpp src/RoadGraph.cpp)
add_executable(tests tests/tests.cpp src/RoadGraph.cpp)

target_link_libraries(graphs rapidcsv)
target_link_libraries(tests rapidcsv)