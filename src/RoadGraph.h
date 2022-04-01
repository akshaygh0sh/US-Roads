#include<vector>
#include<cassert>

struct Edge {
    size_t end;
    double length;
};

struct RoadNode {
    size_t index;
    double x, y;
    std::vector<Edge> edges;
};

class RoadGraph {
public:
    RoadGraph(const std::vector<double> & x_coords, const std::vector<double> & y_coords, const std::vector<size_t>& edge_starts, const std::vector<size_t>& edge_ends, const std::vector<double> & edge_distances): nodes(x_coords.size()){
        assert(x_coords.size() == y_coords.size());
        assert(edge_starts.size() == edge_ends.size());
        assert(edge_starts.size() == edge_distances.size());

        for(size_t i = 0; i < nodes.size(); i++){
            nodes[i].index = i;
            nodes[i].x = x_coords[i];
            nodes[i].y = y_coords[i];
        }

        for(size_t i = 0; i < edge_starts.size(); i++){
            auto start = edge_starts[i];
            auto end = edge_ends[i];
            auto dist = edge_distances[i];

            nodes.at(start).edges.push_back({end, dist});
            nodes.at(end).edges.push_back({start, dist});
        }
    }
private:
    std::vector<RoadNode> nodes;
};