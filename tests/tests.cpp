#define CATCH_CONFIG_MAIN
#include <rapidcsv.h>

#include "../src/RoadGraph.h"
#include "catch.hpp"

RoadGraph load_graph(std::string node, std::string edge){
  rapidcsv::Document nodes(node.c_str(),
                           rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto x_coords = nodes.GetColumn<double>(1);
  auto y_coords = nodes.GetColumn<double>(2);

  rapidcsv::Document edges(edge.c_str(),
                           rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto from = edges.GetColumn<size_t>(1);
  auto to = edges.GetColumn<size_t>(2);
  auto length = edges.GetColumn<double>(3);

  return {x_coords, y_coords, from, to, length};
}

TEST_CASE("Shortest Path Small Simple", "[shortestPath]") {
  auto graph = load_graph("data/small_tests_node.txt", "data/small_tests_edge.txt");

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
  auto graph = load_graph("data/small_tests_node.txt", "data/small_tests_edge.txt");

  auto salesman_17_12_15_19 = graph.shortestSalesman({17, 12, 15, 19}).value();
  std::vector<size_t> actual_path_17_12_15_19 {17, 2, 19, 1, 7, 15, 4, 12};

  
  REQUIRE(salesman_17_12_15_19.first == actual_path_17_12_15_19);
  REQUIRE(salesman_17_12_15_19.second == 54.2415);
}

TEST_CASE("Shortest Path A Star Simple", "[shortestPathAStar]") {
  auto graph = load_graph("data/small_tests_node.txt", "data/small_tests_edge.txt");

  auto A_star_path_14_13 = graph.shortestPathAStar(14, 13).value();
  std::vector<size_t> A_star_actual_path_14_13{14, 16, 3, 13};

  REQUIRE(A_star_path_14_13.first == A_star_actual_path_14_13);
  REQUIRE(A_star_path_14_13.second == 127.05);

  auto A_star_path_10_18 = graph.shortestPathAStar(10, 18).value();
  std::vector<size_t> A_star_actual_path_10_18{10, 0, 1, 7, 5, 18};

  REQUIRE(A_star_path_10_18.first == A_star_actual_path_10_18);
  REQUIRE(A_star_path_10_18.second == 122.56);
}

TEST_CASE("Comparing Shortest Path and Shortest Path A star Simple", "[shortestSalesman], [shortestPathAStar]") {
  auto graph = load_graph("data/small_tests_node.txt", "data/small_tests_edge.txt");

  auto path_14_13 = graph.shortestPath(14, 13).value();
  auto path_10_18 = graph.shortestPath(10, 18).value();
  auto path_9_7 = graph.shortestPath(9, 7).value();

  auto A_star_path_14_13 = graph.shortestPathAStar(14, 13).value();
  auto A_star_path_10_18 = graph.shortestPathAStar(10, 18).value();
  auto A_star_path_9_7 = graph.shortestPathAStar(9, 7).value();


  REQUIRE(path_14_13.first == A_star_path_14_13.first);
  REQUIRE(path_14_13.second == A_star_path_14_13.second);

  REQUIRE(path_10_18.first == A_star_path_10_18.first);
  REQUIRE(path_10_18.second == A_star_path_10_18.second);

  REQUIRE(path_9_7.first == A_star_path_9_7.first);
  REQUIRE(path_9_7.second == A_star_path_9_7.second);

}

TEST_CASE("Comparing Shortest Path and Shortest Path A star Medium", "[shortestSalesman], [shortestPathAStar]") {
  auto graph = load_graph("data/small_tests_node.txt", "data/small_tests_edge.txt");

  auto path_9_11 = graph.shortestPath(9, 11).value();
  auto path_18_20 = graph.shortestPath(18, 20).value();
  auto path_6_10 = graph.shortestPath(6, 10).value();

  auto A_star_path_9_11 = graph.shortestPathAStar(9, 11).value();
  auto A_star_path_18_20 = graph.shortestPath(18, 20).value();
  auto A_star_path_6_10 = graph.shortestPath(6, 10).value();

  REQUIRE(path_9_11.first == A_star_path_9_11.first);
  REQUIRE(path_9_11.second == A_star_path_9_11.second);

  REQUIRE(path_18_20.first == A_star_path_18_20.first);
  REQUIRE(path_18_20.second == A_star_path_18_20.second);

  REQUIRE(path_6_10.first == A_star_path_6_10.first);
  REQUIRE(path_6_10.second == A_star_path_6_10.second);
  
}

