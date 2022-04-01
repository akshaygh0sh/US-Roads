cmake_minimum_required(VERSION 3.10)

project(graph_stuff)

add_subdirectory(rapidcsv)

add_executable(graphs src/main.cpp src/RoadGraph.cpp)

target_link_libraries(graphs rapidcsv)