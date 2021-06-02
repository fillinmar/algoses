#ifndef ARC_GRAPH_HPP
#define ARC_GRAPH_HPP

#include "IGraph.hpp"

class ArcGraph : public IGraph {
 public:
    explicit ArcGraph(size_t vertices_count);
    ArcGraph(IGraph *graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override { return verticesCount; }

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

 private:
    int verticesCount;
    std::vector<std::pair<int, int>> array;
};

#endif
