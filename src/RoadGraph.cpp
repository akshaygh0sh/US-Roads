#include "RoadGraph.h"
#include<limits>
#include<algorithm>

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

std::optional<std::vector<size_t>> RoadGraph::shortestPath(size_t start, size_t end) {
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
      if(distances[e.end] > distance + e.length){
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
  return path;
}