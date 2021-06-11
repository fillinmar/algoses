#include "matrix_graph.hpp"

void push_front(std::vector<int>& arr, int data) {
    arr.push_back(0);
    for (size_t i = arr.size() - 1; i > 0; --i) {
        arr[i] = arr[i - 1];
    }
    arr[0] = data;
}

void MatrixGraph::AddEdge(int from, int to) {
    liste_d_adjacence_[from].push_back(to);
    //  push_front(adjacencyLists[from], to);
}

int MatrixGraph::VerticesCount() const {
    return liste_d_adjacence_.size();
}

MatrixGraph::MatrixGraph(const IGraph &copiant) {
    size_t c_size = copiant.VerticesCount();
    liste_d_adjacence_ = std::vector<std::vector<int>>(c_size);
    for (size_t i = 0; i < c_size; ++i) {
        std::vector<int> vertices = GetNextVertices(i);
        for (size_t j = 0; j < vertices.size(); ++j) {
            AddEdge(i, vertices[j]);
        }
    }
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> vertices;
    for (auto i : liste_d_adjacence_[vertex]) {
        vertices.push_back(i);
    }
    return vertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vertices;
    for (size_t i = 0; i < liste_d_adjacence_.size(); ++i) {
        for (auto j : liste_d_adjacence_[i]) {
            if (j == vertex) {
                vertices.push_back(i);
            }
        }
    }
    return vertices;
}