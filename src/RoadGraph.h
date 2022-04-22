#pragma once
#include <cassert>
#include <optional>
#include <queue>
#include <cmath>
#include <vector>

class RoadGraph {
 public:
  RoadGraph(const std::vector<double> &x_coords,
            const std::vector<double> &y_coords,
            const std::vector<size_t> &edge_starts,
            const std::vector<size_t> &edge_ends,
            const std::vector<double> &edge_distances);

  std::optional<std::pair<std::vector<size_t>, double>> shortestPathDijkstra(
      size_t start, size_t end);
  std::optional<std::pair<std::vector<size_t>, double>> shortestPath(
      size_t start, size_t end);
  std::optional<std::pair<std::vector<size_t>, double>> shortestSalesmanDijkstra(
      const std::vector<size_t> &nodes);

  std::optional<std::pair<std::vector<size_t>, double>> shortestSalesman(
      const std::vector<size_t> &nodes);


  double distance(size_t n1, size_t n2){
    auto dx = nodes[n1].x - nodes[n2].x;
    auto dy = nodes[n1].y - nodes[n2].y;
    return std::sqrt(dx*dx + dy*dy);
  }
 private:
  struct Edge {
    size_t end;
    double length;
  };

  struct RoadNode {
    size_t index;
    double x, y;
    std::vector<Edge> edges;
  };
  std::vector<RoadNode> nodes;
};