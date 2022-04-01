#include <cassert>
#include <vector>

class RoadGraph {
public:
  RoadGraph(const std::vector<double> &x_coords,
            const std::vector<double> &y_coords,
            const std::vector<size_t> &edge_starts,
            const std::vector<size_t> &edge_ends,
            const std::vector<double> &edge_distances);

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