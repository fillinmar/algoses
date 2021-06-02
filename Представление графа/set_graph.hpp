#ifndef SET_GRAPH_HPP
#define SET_GRAPH_HPP

#include <unordered_set>
#include <list>

#include "IGraph.hpp"

class SetGraph : IGraph {
 public:
    SetGraph(unsigned int verticesNumber);
    explicit SetGraph(const IGraph &copy);

    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;
 private:
    unsigned int verticesNumber;
    std::vector<std::unordered_set<int>> out;
    std::vector<std::unordered_set<int>> in;
};

#endif //C_SET_GRAPH_HPP