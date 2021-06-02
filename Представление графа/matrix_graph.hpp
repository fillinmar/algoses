#ifndef MATRIX_GRAPH_HPP
#define MATRIX_GRAPH_HPP

#include "IGraph.hpp"

class MatrixGraph : public IGraph {
 public:
    MatrixGraph(int n) : liste_d_adjacence_(n) {};
    explicit MatrixGraph(const IGraph &copiant);

    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;
 private:
    std::vector<std::vector<int>> liste_d_adjacence_;
};

#endif //MATRIX_GRAPH_HPP
