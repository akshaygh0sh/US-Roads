#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
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

TEST_CASE("Large set dijkstra = astar shortest", "[shortestAStar]") {
  auto graph = load_graph("data/NA.cnode.txt", "data/NA.cedge.txt");

  auto shortest_djikstra1 = graph.shortestPath(0, 2).value();
  auto shortest_astar1 = graph.shortestPathAStar(0, 2).value();

  REQUIRE(shortest_djikstra1 == shortest_astar1);

  
  auto shortest_djikstra2 = graph.shortestPath(0, 10000).value();
  auto shortest_astar2 = graph.shortestPathAStar(0, 10000).value();

  REQUIRE(shortest_djikstra2 == shortest_astar2);

  auto shortest_djikstra3 = graph.shortestPath(4000, 15000).value();
  auto shortest_astar3 = graph.shortestPathAStar(4000, 15000).value();

  REQUIRE(shortest_djikstra3 == shortest_astar3);
}

TEST_CASE("AStar prefomrance", "[APerf]") {
  auto graph = load_graph("data/NA.cnode.txt", "data/NA.cedge.txt");

  BENCHMARK("Dijkstra small"){
    return graph.shortestPath(0, 10);
  };

  BENCHMARK("AStar small"){
    return graph.shortestPathAStar(0, 10);
  };

  BENCHMARK("Dijkstra big"){
    return graph.shortestPath(1000, 50000);
  };

  BENCHMARK("AStar big"){
    return graph.shortestPathAStar(1000, 50000);
  };

  BENCHMARK("Dijkstra salesman"){
    return graph.shortestSalesman({0,1,1000,10000, 150, 50000});
  };

  BENCHMARK("AStar salesman"){
    return graph.shortestSalesmanAStar({0,1,1000,10000, 150, 50000});
  };
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

