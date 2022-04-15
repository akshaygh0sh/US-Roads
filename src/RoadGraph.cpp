#include "RoadGraph.h"
#include<limits>
#include<algorithm>
#include<chrono>
#include<iostream>
#include<string_view>
#include<unordered_map>

RoadGraph::RoadGraph(const std::vector<double> &x_coords,
                     const std::vector<double> &y_coords,
                     const std::vector<size_t> &edge_starts,
                     const std::vector<size_t> &edge_ends,
                     const std::vector<double> &edge_distances)
    : nodes(x_coords.size()) {
  assert(x_coords.size() == y_coords.size());
  assert(edge_starts.size() == edge_ends.size());
  assert(edge_starts.size() == edge_distances.size());

  for (size_t i = 0; i < nodes.size(); i++) {
    nodes[i].index = i;
    nodes[i].x = x_coords[i];
    nodes[i].y = y_coords[i];
  }

  for (size_t i = 0; i < edge_starts.size(); i++) {
    auto start = edge_starts[i];
    auto end = edge_ends[i];
    auto dist = edge_distances[i];

    nodes.at(start).edges.push_back({end, dist});
    nodes.at(end).edges.push_back({start, dist});
  }

}

std::optional<std::pair<std::vector<size_t>, double>> RoadGraph::shortestPath(size_t start, size_t end) {
  std::priority_queue<std::pair<double, size_t>, std::vector<std::pair<double, size_t>>, std::greater<>> pq{}; 
  std::vector<bool> visited(nodes.size(), false);
  std::vector<double> distances(nodes.size(), std::numeric_limits<double>::infinity());
  std::vector<size_t> paths(nodes.size(), 0);

  pq.push({0.0, start}); 

  while (!pq.empty()) {

    auto [distance, index] = pq.top();
    pq.pop();
    if(index == end) break;

    if(visited[index]) continue;
    visited[index] = true;

    
    for(auto const& e : nodes[index].edges){
      if(!visited[e.end] && distances[e.end] > distance + e.length){
        distances[e.end] = distance + e.length;
        pq.push({distance + e.length, e.end});
        paths[e.end] = index;
      }
    }
  }


  if(distances[end] == std::numeric_limits<double>::infinity()){
    return std::nullopt;
  }
  std::vector<size_t> path;

  for(size_t i = end; i != start; i = paths[i]){
    path.push_back(i);
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());
  return {{path, distances[end]}};
}


std::optional<std::pair<std::vector<size_t>, double>> RoadGraph::shortestSalesman(const std::vector<size_t>& nodes){
  auto node_order = nodes;

  std::pair<std::vector<size_t>, double> best = {{}, std::numeric_limits<double>::infinity()};


  auto hash = [](std::pair<size_t, size_t> a){
    size_t mem[] = {a.first, a.second};
    return std::hash<std::string_view>()({(char*)mem, 8});
  };
  std::unordered_map<std::pair<size_t, size_t>, std::pair<std::vector<size_t>, double>, decltype(hash)> path_cache{nodes.size()*nodes.size(), hash};

  for(auto i = nodes.begin(); i != nodes.end(); i++){
    for(auto j = i + 1; j != nodes.end(); j++){
      auto path = shortestPath(*i, *j);
      if(!path.has_value()) return std::nullopt;
      path_cache[{*i, *j}] = *path;
      std::reverse(path->first.begin(), path->first.end());
      path_cache[{*j, *i}] = *path;
    }
  }

  do {
    std::vector<size_t> current_path = {node_order[0]};
    double current_distance = 0;

    for(size_t i = 0; i < node_order.size() - 1; i++){
      size_t node1 = node_order[i];
      size_t node2 = node_order[i+1];

      const auto& path = path_cache.at({node1, node2});
      current_path.insert(current_path.end(), path.first.begin() + 1, path.first.end());
      current_distance += path.second;
    }

    if(current_distance < best.second){
      best = {current_path, current_distance};
    }

    std::next_permutation(node_order.begin(), node_order.end());
  } while(node_order != nodes);
  return best;
}