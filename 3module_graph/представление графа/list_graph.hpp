#ifndef LIST_GRAPH_HPP
#define LIST_GRAPH_HPP

#include <list>

#include "IGraph.hpp"

class ListGraph : IGraph {
 public:
    ListGraph(int n)
    : adjacencyLists(n) {};

    explicit ListGraph(const IGraph &copy);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
 private:
    std::vector<std::list<int>> adjacencyLists;
};

#endif //LIST_GRAPH_HPP
