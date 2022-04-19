#define CATCH_CONFIG_MAIN
#include <rapidcsv.h>

#include "../src/RoadGraph.h"
#include "catch.hpp"

TEST_CASE("Shortest Path Small Simple", "[shortestPath]") {
  rapidcsv::Document nodes("data/small_tests_node.txt",
                           rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto x_coords = nodes.GetColumn<double>(1);
  auto y_coords = nodes.GetColumn<double>(2);

  rapidcsv::Document edges("data/small_tests_edge.txt",
                           rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto from = edges.GetColumn<size_t>(1);
  auto to = edges.GetColumn<size_t>(2);
  auto length = edges.GetColumn<double>(3);

  RoadGraph graph{x_coords, y_coords, from, to, length};

  // Vars are defined as path_start_end
  auto path_14_13 = graph.shortestPath(14, 13).value();
  std::vector<size_t> actual_path_14_13{14, 16, 3, 13};

  REQUIRE(path_14_13.first == actual_path_14_13);
  REQUIRE(path_14_13.second == 127.05);

  auto path_10_18 = graph.shortestPath(10, 18).value();
  std::vector<size_t> actual_path_10_18{10, 0, 1, 7, 5, 18};

  REQUIRE(path_10_18.first == actual_path_10_18);
  REQUIRE(path_10_18.second == 122.56);
}

TEST_CASE("Shortest Travelling Salesman Simple", "[shortestSalesman]") {
  rapidcsv::Document nodes("data/small_tests_node.txt",
                           rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto x_coords = nodes.GetColumn<double>(1);
  auto y_coords = nodes.GetColumn<double>(2);

  rapidcsv::Document edges("data/small_tests_edge.txt",
                           rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto from = edges.GetColumn<size_t>(1);
  auto to = edges.GetColumn<size_t>(2);
  auto length = edges.GetColumn<double>(3);

  RoadGraph graph{x_coords, y_coords, from, to, length};
  auto salesman_17_12_15_19 = graph.shortestSalesman({17, 12, 15, 19}).value();
  std::vector<size_t> actual_path_17_12_15_19 {17, 8, 13, 12, 4, 15, 7, 1, 19};

  REQUIRE(salesman_17_12_15_19.first == actual_path_17_12_15_19);
  REQUIRE(salesman_17_12_15_19.second == 100.1);
}