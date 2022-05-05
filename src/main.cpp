#include <rapidcsv.h>

#include <chrono>
#include <iostream>
#include "RoadGraph.h"


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <sstream>
#include <optional>

int main(){
  EM_ASM( module_loaded());
}

extern "C" EMSCRIPTEN_KEEPALIVE RoadGraph* init(char * nodes_str, char * edges_str) {
  std::stringstream nodes_stream{nodes_str};
  std::stringstream edges_stream{edges_str};

  rapidcsv::Document nodes(nodes_stream, rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto x_coords = nodes.GetColumn<double>(1);
  auto y_coords = nodes.GetColumn<double>(2);

  rapidcsv::Document edges(edges_stream, rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto from = edges.GetColumn<size_t>(1);
  auto to = edges.GetColumn<size_t>(2);
  auto length = edges.GetColumn<double>(3);

  return new RoadGraph{x_coords, y_coords, from, to, length};
}

extern "C" EMSCRIPTEN_KEEPALIVE int* path(RoadGraph * graph, int start, int end) {
  auto path = graph->shortestPath(start, end).value().first;
  int* ret = new int[path.size() + 1];
  ret[0] = path.size();
  std::copy(path.begin(), path.end(), ret + 1);
  return ret;
}

extern "C" EMSCRIPTEN_KEEPALIVE void delete_arr(int * arr){
  delete arr;
}

#else

void cmd_line_path(RoadGraph& graph){
  std::cout << "point 1 index: ";
  int p1, p2;
  std::cin >> p1;
  std::cout << "point 2 index: ";
  std::cin >> p2;
  auto path = graph.shortestPath(p1, p2);
  if(!path.has_value()){
    std::cout << "no path between points" << std::endl;
  } else {
    std::cout << "Distance: " << path->second << std::endl;
    std::cout << "nodes: " << std::endl;
    for(auto i : path->first){
      std::cout << i << ", ";
    }
    std::cout << '\n';
  }
}

void cmd_line_salesman(RoadGraph& graph){
  std::cout << "enter visited node indeces (terminate with -1)" << std::endl;

  std::vector<std::size_t> nodes;
  while(true){
    int i;
    std::cin >> i;
    if(i == -1) break;
    nodes.push_back(i);
  }

  auto path = graph.shortestSalesman(nodes);
  if(!path.has_value()){
    std::cout << "no path between points" << std::endl;
  } else {
    std::cout << "Distance: " << path->second << std::endl;
    std::cout << "nodes: " << std::endl;
    for(auto i : path->first){
      std::cout << i << ", ";
    }
    std::cout << '\n';
  }
}


int main() {
  std::cout << 
R"(
Use defualt data location (y/n)
)";

  std::string file_loc_chooser;
  std::cin >> file_loc_chooser;
  std::string node_location = "data/NA.cnode.txt";
  std::string edge_location = "data/NA.cedge.txt";

  if(!file_loc_chooser.empty() && (file_loc_chooser[0] == 'n' || file_loc_chooser[0] == 'N')){
    std::cout << "Chose node data location" << std::endl;
    std::cin >> node_location;
    std::cout << "Chose edge data location" << std::endl;
    std::cin >> edge_location;
  }

  rapidcsv::Document nodes(node_location, rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto x_coords = nodes.GetColumn<double>(1);
  auto y_coords = nodes.GetColumn<double>(2);

  rapidcsv::Document edges(edge_location, rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(' '));
  auto from = edges.GetColumn<size_t>(1);
  auto to = edges.GetColumn<size_t>(2);
  auto length = edges.GetColumn<double>(3);

  RoadGraph graph{x_coords, y_coords, from, to, length};
  

  while(true){
    std::cout << 
R"(
  Pick option
    1: shortest path
    2: shortest salesman
  )";

    int option;
    std::cin >> option;

    switch(option){
      case 1:
        cmd_line_path(graph);
        break;
      case 2:
        cmd_line_salesman(graph);
        break;
      default:
        std::cout << "Invalid option" << std::endl;
        break;
    }
  }
}

#endif