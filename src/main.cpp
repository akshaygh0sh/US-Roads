#include "RoadGraph.h"
#include <iostream>
#include <rapidcsv.h>
#include <chrono>

int main() {
  rapidcsv::Document nodes("data/NA.cnode.txt", rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto x_coords = nodes.GetColumn<double>(1);
  auto y_coords = nodes.GetColumn<double>(2);

  rapidcsv::Document edges("data/NA.cedge.txt", rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto from = edges.GetColumn<size_t>(1);
  auto to = edges.GetColumn<size_t>(2);
  auto length = edges.GetColumn<double>(3);

  RoadGraph graph{x_coords, y_coords, from, to, length};


  auto t1 = std::chrono::steady_clock::now();
  auto path = graph.shortestSalesman({0, 1, 2, 3, 170000, 65000, 35000, 70000}).value();
  auto t2 = std::chrono::steady_clock::now();

  std::cout << (t2-t1)/std::chrono::milliseconds(1) << "ms" << std::endl;

  // std::cout << "distance: " << path.second << '\n';
  // for(auto i : path.first){
  //   std::cout << i << ',';
  // }
}